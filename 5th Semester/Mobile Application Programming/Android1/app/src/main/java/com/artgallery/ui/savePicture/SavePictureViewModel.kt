package com.artgallery.ui.savePicture

import android.util.Log
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.viewmodel.initializer
import androidx.lifecycle.viewmodel.viewModelFactory
import com.artgallery.models.picture.PictureRepository
import kotlinx.coroutines.launch
import com.artgallery.core.Result
import com.artgallery.core.TAG
import com.artgallery.models.picture.Picture
import com.artgallery.models.picture.PictureToSave
import com.artgallery.ui.MyApplication


data class ItemUiState(
    val pictureId: String? = null,
    val picture: PictureToSave = PictureToSave(),
    var loadResult: Result<Picture>? = null,
    var submitResult: Result<Picture>? = null,
)

class SavePictureViewModel(private val pictureId: String?, private val pictureRepository: PictureRepository) :
    ViewModel() {

    var uiState: ItemUiState by mutableStateOf(ItemUiState(loadResult = Result.Loading))
        private set

    init {
        Log.d(TAG, "init")
        if (pictureId != null) {
            loadItem()
        } else {
            uiState = uiState.copy(loadResult = Result.Success(Picture()))
        }
    }

    private fun loadItem() {
        viewModelScope.launch {
            uiState = try {
                if (pictureId != null) {
                    uiState.copy(loadResult = Result.Success(pictureRepository.find(pictureId)))
                } else {
                    uiState.copy(pictureId = null, loadResult = Result.Success(Picture()))
                }
            } catch (e: Exception) {
                uiState.copy(loadResult = Result.Error(e))
            }
        }
    }


    fun saveOrUpdateItem(title: String,
                         description: String,
                         typeId: Int) {
        viewModelScope.launch {
            Log.d(TAG, "saveOrUpdateItem...");
            uiState = try {
                uiState = uiState.copy(submitResult = Result.Loading)
                val picture = uiState.picture.copy(
                    id = pictureId,
                    title = title,
                    description = description,
                    typeId = typeId,
                )
                val savedPicture: Picture = if (pictureId == null) {
                    pictureRepository.save(picture)
                } else {
                    pictureRepository.update(picture)
                }
                Log.d(TAG, "saveOrUpdateItem succeeeded");
                uiState.copy(submitResult = Result.Success(savedPicture))
            } catch (e: Exception) {
                Log.d(TAG, "saveOrUpdateItem failed");
                uiState.copy(submitResult = Result.Error(e))
            }
        }
    }

    companion object {
        fun Factory(itemId: String?): ViewModelProvider.Factory = viewModelFactory {
            initializer {
                val app =
                    (this[ViewModelProvider.AndroidViewModelFactory.APPLICATION_KEY] as MyApplication)
                SavePictureViewModel(itemId, app.container.pictureRepository)
            }
        }
    }
}
