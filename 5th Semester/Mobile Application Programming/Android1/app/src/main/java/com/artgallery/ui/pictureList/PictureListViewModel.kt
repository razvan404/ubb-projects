package com.artgallery.ui.pictureList

import android.util.Log
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.viewmodel.initializer
import androidx.lifecycle.viewmodel.viewModelFactory
import com.artgallery.core.TAG
import com.artgallery.models.picture.Picture
import com.artgallery.models.picture.PictureRepository
import com.artgallery.ui.MyApplication
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.launch

class PictureListViewModel(private val picturesRepository: PictureRepository) : ViewModel() {
    val uiState: Flow<List<Picture>> = picturesRepository.pictureStream

    init {
        Log.d(TAG, "init")
        loadItems()
    }

    private fun loadItems() {
        Log.d(TAG, "loadItems...")
        viewModelScope.launch {
            picturesRepository.refresh()
        }
    }

    companion object {
        val Factory: ViewModelProvider.Factory = viewModelFactory {
            initializer {
                val app =
                    (this[ViewModelProvider.AndroidViewModelFactory.APPLICATION_KEY] as MyApplication)
                PictureListViewModel(app.container.pictureRepository)
            }
        }
    }
}
