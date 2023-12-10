package com.artgallery.models.picture

import android.util.Log
import com.artgallery.api.Api
import com.artgallery.core.TAG
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.channels.awaitClose
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.callbackFlow
import kotlinx.coroutines.withContext

class PictureRepository(
    private val pictureService: PictureService,
    private val pictureWsClient: PictureWsClient,
    private val pictureDao: PictureDao
) {
    val pictureStream by lazy { pictureDao.getAll() }

    init {
        Log.d(TAG, "init")
    }

    suspend fun refresh() {
        Log.d(TAG, "refresh started")
        try {
            if (Api.tokenInterceptor.user == null) {
                Log.d(TAG, "refresh skipped")
                return
            }
            val pictures = pictureService.findAll(
                authorId = Api.tokenInterceptor.user?.id ?: ""
            )
            pictureDao.deleteAll()
            pictures.forEach { pictureDao.insert(it) }
            Log.d(TAG, "refresh succeeded")
        } catch (e: Exception) {
            Log.w(TAG, "refresh failed", e)
        }
    }

    suspend fun openWsClient() {
        Log.d(TAG, "openWsClient")
        withContext(Dispatchers.IO) {
            getPictureEvents().collect {
                Log.d(TAG, "Item event collected $it")
                if (it.isSuccess) {
                    val itemEvent = it.getOrNull()
                    when (itemEvent?.type) {
                        "PICTURE_SAVED" -> handlePictureCreated(itemEvent.payload)
                        "PICTURE_UPDATED" -> handlePictureUpdated(itemEvent.payload)
                        "PICTURE_DELETED" -> handlePictureDeleted(itemEvent.payload)
                    }
                }
            }
        }
    }

    suspend fun closeWsClient() {
        Log.d(TAG, "closeWsClient")
        withContext(Dispatchers.IO) {
            pictureWsClient.closeSocket()
        }
    }

    private suspend fun getPictureEvents(): Flow<Result<PictureEvent>> = callbackFlow {
        Log.d(TAG, "getItemEvents started")
        pictureWsClient.openSocket(
            onEvent = {
                Log.d(TAG, "onEvent $it")
                if (it != null) {
                    trySend(Result.success(it))
                }
            },
            onClosed = { close() },
            onFailure = { close() });
        awaitClose { pictureWsClient.closeSocket() }
    }

    suspend fun update(picture: PictureToSave): Picture {
        Log.d(TAG, "update $picture...")
        val updatedPicture =
            pictureService.update(
                id = picture.id,
                picture = picture,
                authorization = Api.getBearerToken()
            )
        Log.d(TAG, "update $picture succeeded")
        handlePictureUpdated(updatedPicture)
        return updatedPicture
    }

    suspend fun save(picture: PictureToSave): Picture {
        Log.d(TAG, "save $picture...")
        val createdPicture = pictureService.create(
            picture = picture, authorization = Api.getBearerToken()
        )
        Log.d(TAG, "save $picture succeeded")
        handlePictureCreated(createdPicture)
        return createdPicture
    }

    suspend fun find(id: String): Picture {
        Log.d(TAG, "find $id...")
        val picture = pictureService.find(id = id)
        Log.d(TAG, "find $id succeeded")
        handlePictureUpdated(picture)
        return picture
    }

    private suspend fun handlePictureDeleted(picture: Picture) {
        Log.d(TAG, "handleItemDeleted - todo $picture")
    }

    private suspend fun handlePictureUpdated(picture: Picture) {
        Log.d(TAG, "handleItemUpdated...")
        pictureDao.update(picture)
    }

    private suspend fun handlePictureCreated(picture: Picture) {
        Log.d(TAG, "handleItemCreated...")
        pictureDao.insert(picture)
    }

    suspend fun deleteAll() {
        pictureDao.deleteAll()
    }

    fun setToken(token: String?) {
        pictureWsClient.authorize(token)
    }
}