package com.example.myfirstapp.pictures.data

import android.util.Log
import com.example.myfirstapp.core.Result
import com.example.myfirstapp.core.TAG
import com.example.myfirstapp.core.data.remote.Api
import com.example.myfirstapp.pictures.data.local.ItemDao
import com.example.myfirstapp.pictures.data.remote.ItemEvent
import com.example.myfirstapp.pictures.data.remote.ItemService
import com.example.myfirstapp.pictures.data.remote.ItemWsClient
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.channels.awaitClose
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.callbackFlow
import kotlinx.coroutines.withContext

class ItemRepository(private val itemService: ItemService,
                     private val itemWsClient: ItemWsClient,
                     private val itemDao: ItemDao) {

    val picturesStream by lazy { itemDao.getAll() }

    init {
        Log.d(TAG, "init")
    }

    suspend fun refresh() {
        Log.d(TAG, "refresh started")
        try {
            val pictures = itemService.find(authorization = getBearerToken())
            itemDao.deleteAll()
            pictures.forEach{ itemDao.insert(it) }
            Log.d(TAG, "refresh succeeded")
        } catch (e: Exception) {
            Log.w(TAG, "refresh failed", e)
        }
    }

    suspend fun openWsClient() {
        Log.d(TAG, "openWsClient")
        withContext(Dispatchers.IO) {
            getItemEvents().collect {
                Log.d(TAG, "Item event collected $it")
                if (it is Result.Success) {
                    val itemEvent = it.data;
                    when (itemEvent.event) {
                        "created" -> handleItemCreated(itemEvent.payload.updatedPicture)
                        "updated" -> handleItemUpdated(itemEvent.payload.updatedPicture)
                        "deleted" -> handleItemDeleted(itemEvent.payload.updatedPicture)
                    }
                }
            }
        }
    }

    suspend fun closeWsClient() {
        Log.d(TAG, "closeWsClient")
        withContext(Dispatchers.IO) {
            itemWsClient.closeSocket()
        }
    }

    suspend fun getItemEvents(): Flow<Result<ItemEvent>> = callbackFlow {
        Log.d(TAG, "getItemEvents started")
        itemWsClient.openSocket(
            onEvent = {
                Log.d(TAG, "onEvent $it")
                if (it != null) {
                    Log.d(TAG, "onEvent trySend $it")
                    trySend(Result.Success(it))
                }
            },
            onClosed = { close() },
            onFailure = { close() });
        awaitClose { itemWsClient.closeSocket() }
    }

    suspend fun update(picture: Picture): Picture {
        Log.d(TAG, "update $picture...")
        picture.isSaved = true
        val updatedItem = itemService.update(authorization = getBearerToken(), picture._id, picture)
        Log.d(TAG, "update $picture succeeded")
        handleItemUpdated(updatedItem)
        return updatedItem
    }

    suspend fun save(picture: Picture): Picture {
        Log.d(TAG, "save $picture...")
        picture.isSaved = true
        val createdItem = itemService.create(authorization = getBearerToken(), picture)
        Log.d(TAG, "save $picture succeeded")
        Log.d(TAG, "handle created $createdItem")
        handleItemCreated(createdItem)
        deletePicture(createdItem.title, false)
        return createdItem
    }

    suspend fun addLocally(picture: Picture){
        itemDao.insert(picture);
    }

    suspend fun deleteLocally(){
        itemDao.getLocalPictures(isSaved = false)
    }

    suspend fun getLocallySaved(): List<Picture>{
        return itemDao.getLocalPictures(isSaved = false)
    }

    suspend fun updateLocally(picture: Picture){
        Log.d(TAG, "Updating picture locally: ${picture}")
        itemDao.update(picture)
    }

    private suspend fun handleItemDeleted(picture: Picture) {
        Log.d(TAG, "handleItemDeleted - todo $picture")
    }

    private suspend fun handleItemUpdated(picture: Picture) {
        Log.d(TAG, "handleItemUpdated...: $picture")
        itemDao.update(picture)
    }

    private suspend fun handleItemCreated(picture: Picture) {
        Log.d(TAG, "handleItemCreated...: $picture")
        itemDao.insert(picture)
    }

    suspend fun deleteAll(){
        itemDao.deleteAll()
    }

    suspend fun deletePicture(title: String, isSaved: Boolean) {
        Log.d(TAG, "deleting not saved: ${title}, ${isSaved}")
        itemDao.deletePictureNotSaved(title, isSaved)
    }

    suspend fun getNrUnsaved(): Int{
        return itemDao.getNotSaved(false)
    }

    fun setToken(token: String) {
        itemWsClient.authorize(token)
    }

    private fun getBearerToken() = "Bearer ${Api.tokenInterceptor.token}"
}