package com.artgallery.api

import android.util.Log
import com.artgallery.core.TAG
import com.artgallery.models.user.User
import okhttp3.Interceptor
import okhttp3.Response

class TokenInterceptor : Interceptor {
    var token: String? = null
    var user: User? = null

    override fun intercept(chain: Interceptor.Chain): Response {
        val original = chain.request()
        val originalUrl = original.url
        if (token == null) {
            Log.d(TAG, "Token is null")
            return chain.proceed(original)
        }
        val requestBuilder = original.newBuilder()
            .addHeader("Authorization", "Bearer $token")
            .url(originalUrl)
        val request = requestBuilder.build()
        Log.d(TAG, "Authorization bearer added")
        return chain.proceed(request)
    }
}