package com.artgallery.models.user

import kotlinx.serialization.Serializable

@Serializable
data class User (
    val id: String?,
    val username: String,
    val profileImage: String?,
    val email: String?,
    val password: String?,
)
