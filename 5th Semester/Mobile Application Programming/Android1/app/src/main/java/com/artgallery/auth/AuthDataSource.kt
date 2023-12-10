package com.artgallery.auth

import android.util.Log
import com.artgallery.core.TAG
import com.artgallery.api.Api
import com.artgallery.models.user.User


class AuthDataSource {
    private val authService: AuthService = Api.retrofit.create(AuthService::class.java)

    suspend fun login(user: LoginRequest): Result<LoginResponse> {
        return try {
            Result.success(authService.login(user))
        } catch (e: Exception) {
            Log.w(TAG, "login failed", e)
            Result.failure(e)
        }
    }
}
