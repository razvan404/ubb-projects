package com.example.myfirstapp.sensors

import ProximitySensorMonitor
import android.app.Application
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableFloatStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.viewmodel.initializer
import androidx.lifecycle.viewmodel.viewModelFactory
import kotlinx.coroutines.launch

class ProximitySensorViewModel(application: Application) : AndroidViewModel(application) {
    var uiState by mutableFloatStateOf(0f)

    init {
        viewModelScope.launch {
            ProximitySensorMonitor(getApplication()).proximityValue.collect {
                uiState = it
            }
        }
    }

    companion object {
        fun Factory(application: Application): ViewModelProvider.Factory = viewModelFactory {
            initializer {
                ProximitySensorViewModel(application)
            }
        }
    }
}