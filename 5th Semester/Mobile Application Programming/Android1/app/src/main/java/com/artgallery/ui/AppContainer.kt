package com.artgallery.ui

import android.content.Context
import android.util.Log
import androidx.datastore.preferences.preferencesDataStore
import com.artgallery.api.Api
import com.artgallery.auth.AuthDataSource
import com.artgallery.auth.AuthRepository
import com.artgallery.core.TAG
import com.artgallery.AppDatabase
import com.artgallery.models.picture.PictureRepository
import com.artgallery.models.picture.PictureService
import com.artgallery.models.picture.PictureWsClient
import com.artgallery.userPreferences.UserPreferencesRepository

val Context.userPreferencesDataStore by preferencesDataStore(
    name = "user_preferences"
)

class AppContainer(private val context: Context) {
    init {
        Log.d(TAG, "init")
    }

    private val pictureService: PictureService = Api.retrofit.create(PictureService::class.java)
    private val pictureWsClient: PictureWsClient = PictureWsClient(Api.okHttpClient)
    private val authDataSource: AuthDataSource = AuthDataSource()

    private val database: AppDatabase by lazy { AppDatabase.getDatabase(context) }

    val pictureRepository: PictureRepository by lazy {
        PictureRepository(pictureService, pictureWsClient, database.pictureDao())
    }

    val authRepository: AuthRepository by lazy {
        AuthRepository(authDataSource)
    }

    val userPreferencesRepository: UserPreferencesRepository by lazy {
        UserPreferencesRepository(context.userPreferencesDataStore)
    }
}
