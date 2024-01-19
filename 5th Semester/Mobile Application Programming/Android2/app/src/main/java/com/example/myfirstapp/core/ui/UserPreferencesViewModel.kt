package com.example.myfirstapp.core.ui

import android.util.Log
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.viewmodel.initializer
import androidx.lifecycle.viewmodel.viewModelFactory
import com.example.myfirstapp.MyFirstApplication
import com.example.myfirstapp.core.TAG
import com.example.myfirstapp.core.data.UserPreferences
import com.example.myfirstapp.core.data.UserPreferencesRepository
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.launch

class UserPreferencesViewModel(private val userPreferencesRepository: UserPreferencesRepository) :
    ViewModel() {
    val uiState: Flow<UserPreferences> = userPreferencesRepository.userPreferencesStream

    init {
        Log.d(TAG, "init")
    }

    fun save(userPreferences: UserPreferences) {
        viewModelScope.launch {
            Log.d(TAG, "saveUserPreferences...");
            userPreferencesRepository.save(userPreferences)
        }
    }

    companion object {
        val Factory: ViewModelProvider.Factory = viewModelFactory {
            initializer {
                val app =
                    (this[ViewModelProvider.AndroidViewModelFactory.APPLICATION_KEY] as MyFirstApplication)
                UserPreferencesViewModel(app.container.userPreferencesRepository)
            }
        }
    }
}

