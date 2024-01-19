package com.example.myfirstapp.pictures.ui.items

import android.util.Log
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.viewmodel.initializer
import androidx.lifecycle.viewmodel.viewModelFactory
import com.example.myfirstapp.MyFirstApplication
import com.example.myfirstapp.core.TAG
import com.example.myfirstapp.pictures.data.Picture
import com.example.myfirstapp.pictures.data.ItemRepository
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.launch

class ItemsViewModel(private val itemRepository: ItemRepository) : ViewModel() {
    val uiState: Flow<List<Picture>> = itemRepository.picturesStream

    init {
        Log.d(TAG, "init")
        loadItems()
    }

    fun loadItems() {
        Log.d(TAG, "loadItems...")
        viewModelScope.launch {
            itemRepository.refresh()
        }
    }

    companion object {
        val Factory: ViewModelProvider.Factory = viewModelFactory {
            initializer {
                val app =
                    (this[ViewModelProvider.AndroidViewModelFactory.APPLICATION_KEY] as MyFirstApplication)
                ItemsViewModel(app.container.itemRepository)
            }
        }
    }
}
