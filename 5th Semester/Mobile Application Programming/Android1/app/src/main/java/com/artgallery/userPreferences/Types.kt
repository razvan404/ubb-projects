package com.artgallery.userPreferences

import com.artgallery.models.user.User

data class UserPreferences(
    val user: User? = null,
    val token: String? = ""
)