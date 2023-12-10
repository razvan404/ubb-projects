package com.artgallery.api

import com.google.gson.GsonBuilder
import okhttp3.OkHttpClient
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory
import java.util.concurrent.TimeUnit

object Api {
    private const val url = "192.168.43.186:8000"
    private const val httpUrl = "http://$url/"
    const val wsUrl = "ws://$url"

    private var gson = GsonBuilder().create()
    val tokenInterceptor = TokenInterceptor()

    fun getImageUrl(imageId: String) = "http://$url/uploads/$imageId"

    fun getBearerToken() = "Bearer ${Api.tokenInterceptor.token}"

    val okHttpClient = OkHttpClient.Builder().apply {
        this.addInterceptor(tokenInterceptor)
        this.callTimeout(60, TimeUnit.SECONDS) // Set the timeout here
    }.build()



    val retrofit = Retrofit.Builder()
        .baseUrl(httpUrl)
        .addConverterFactory(GsonConverterFactory.create(gson))
//        .client(okHttpClient) // does not work in android with the latest libs
        .build()
}