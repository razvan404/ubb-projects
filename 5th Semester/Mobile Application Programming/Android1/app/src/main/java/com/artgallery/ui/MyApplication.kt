package com.artgallery.ui

import android.app.Application
import android.util.Log
import com.artgallery.core.TAG
import com.artgallery.ui.AppContainer

class MyApplication : Application() {
    lateinit var container: AppContainer

    override fun onCreate() {
        super.onCreate()
        Log.d(TAG, "init")
        container = AppContainer(this)
    }
}
