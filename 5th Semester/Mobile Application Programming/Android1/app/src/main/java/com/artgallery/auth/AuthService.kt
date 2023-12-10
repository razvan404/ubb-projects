package com.artgallery.auth

import com.artgallery.models.user.User
import retrofit2.http.Body
import retrofit2.http.Headers
import retrofit2.http.POST


data class LoginRequest(
    val usernameOrEmail: String,
    val password: String
)

data class LoginResponse(
    val user: User,
    val token: String
)

interface AuthService {
    @Headers("Content-Type: application/json")
    @POST("/api/auth/login")
    suspend fun login(@Body user: LoginRequest): LoginResponse
}
