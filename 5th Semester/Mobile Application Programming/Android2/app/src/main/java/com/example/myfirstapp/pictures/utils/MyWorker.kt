package com.example.myfirstapp.pictures.utils

import android.content.Context
import android.util.Log
import androidx.work.CoroutineWorker
import androidx.work.WorkerParameters
import com.example.myfirstapp.MyFirstApplication

class MyWorker(
    context: Context,
    val workerParams: WorkerParameters,
) : CoroutineWorker(context, workerParams) {
    init {
        Log.d("MyWorker", "init")
    }
    override suspend fun doWork(): Result {
        val itemRepository = (applicationContext as MyFirstApplication).container.itemRepository

        val notSaved = itemRepository.getLocallySaved()
        Log.d("MyWorker", notSaved.toString())

        notSaved.forEach{ picture ->
            if(picture._id.length < 10){
                picture._id = ""
                val res = itemRepository.save(picture)  // am pus isSaved = true in repository
            }
            else{
                var res = itemRepository.update(picture)
            }
        }
        return Result.success()
    }
}