package com.artgallery.auth

import android.util.Log
import com.artgallery.core.TAG
import com.artgallery.api.Api
import com.artgallery.models.user.User

class AuthRepository(private val authDataSource: AuthDataSource) {
    init {
        Log.d(TAG, "init")
    }

    fun logout() {
        Api.tokenInterceptor.token = null
    }

    suspend fun login(usernameOrEmail: String, password: String): Result<LoginResponse> {
        val user = LoginRequest(usernameOrEmail, password)
        val result = authDataSource.login(user)
        if (result.isSuccess) {
            Api.tokenInterceptor.token = result.getOrNull()?.token
            Api.tokenInterceptor.user = result.getOrNull()?.user
        }
        return result
    }
}