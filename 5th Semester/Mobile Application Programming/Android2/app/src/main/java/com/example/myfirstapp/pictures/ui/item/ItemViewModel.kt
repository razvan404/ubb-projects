package com.example.myfirstapp.pictures.ui.item

import android.util.Log
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.viewmodel.initializer
import androidx.lifecycle.viewmodel.viewModelFactory
import com.example.myfirstapp.MyFirstApplication
import com.example.myfirstapp.core.Result
import com.example.myfirstapp.core.TAG
import com.example.myfirstapp.pictures.data.Picture
import com.example.myfirstapp.pictures.data.ItemRepository
import kotlinx.coroutines.launch

data class ItemUiState(
    val itemId: String? = null,
    val picture: Picture = Picture(),
    var loadResult: Result<Picture>? = null,
    var submitResult: Result<Picture>? = null,
)

class ItemViewModel(private val itemId: String?, private val itemRepository: ItemRepository) :
    ViewModel() {

    var uiState: ItemUiState by mutableStateOf(ItemUiState(loadResult = Result.Loading))
        private set

    init {
        Log.d(TAG, "init with id: ${itemId}")
        if (itemId != null) {
            loadItem()
        } else {
            uiState = uiState.copy(loadResult = Result.Success(Picture()))
        }
    }

    fun loadItem() {
        viewModelScope.launch {
            itemRepository.picturesStream.collect { items ->
                if (!(uiState.loadResult is Result.Loading)) {
                    return@collect
                }
                Log.d(TAG, "searching for ${itemId}")
                val picture = items.find { it._id == itemId } ?: Picture()
                Log.d(TAG, "found ${picture}")
                uiState = uiState.copy(picture = picture, loadResult = Result.Success(picture))
            }
        }
    }

    fun saveItem(title: String, description: String, imageUrl: String, dateOfRelease: String, isPhotography: Boolean){
        viewModelScope.launch {
            Log.d(TAG, "save new picture");
            try{
                uiState = uiState.copy(submitResult = Result.Loading)
                val item = uiState.picture.copy(title=title, description = description, imageUrl = imageUrl, dateOfRelease = dateOfRelease, isPhotography = isPhotography, _id = "")
                val savedPicture: Picture;
                savedPicture = itemRepository.save(item)
                Log.d(TAG, "save picture succeeded");
                uiState = uiState.copy(submitResult = Result.Success(savedPicture))
            }catch (e: Exception){
                Log.d(TAG, "saveOrUpdateItem failed");
                val nrUnsaved = itemRepository.getNrUnsaved()
                val currentId = nrUnsaved + 1
                uiState = uiState.copy(submitResult = Result.Error(e))
                val item = uiState.picture.copy(title=title, description = description, imageUrl = imageUrl, dateOfRelease = dateOfRelease, isPhotography = isPhotography, isSaved = false, _id = currentId.toString())
                itemRepository.addLocally(item);
                Log.d(TAG, "added item ${item} locally");
            }
        }
    }

    fun updateItem(title: String, description: String, lat: Double, lon: Double) {
        viewModelScope.launch {
            Log.d(TAG, "update picture");
            try {
                uiState = uiState.copy(submitResult = Result.Loading)
                val item = uiState.picture.copy(title=title, description = description, isSaved = true, lat = lat, lon = lon)
                val savedPicture: Picture;
                savedPicture = itemRepository.update(item)
                Log.d(TAG, "UpdateItem succeeeded");
                uiState = uiState.copy(submitResult = Result.Success(savedPicture))
            } catch (e: Exception) {
                Log.d(TAG, "saveOrUpdateItem failed");
                uiState = uiState.copy(submitResult = Result.Error(e))
                val item = uiState.picture.copy(title=title, description = description, isSaved = false, lat=lat, lon=lon)
                itemRepository.updateLocally(item)
            }
        }
    }

    companion object {
        fun Factory(itemId: String?): ViewModelProvider.Factory = viewModelFactory {
            initializer {
                val app =
                    (this[ViewModelProvider.AndroidViewModelFactory.APPLICATION_KEY] as MyFirstApplication)
                ItemViewModel(itemId, app.container.itemRepository)
            }
        }
    }
}
