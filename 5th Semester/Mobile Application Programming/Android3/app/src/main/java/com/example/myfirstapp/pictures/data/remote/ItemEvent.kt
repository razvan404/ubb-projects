package com.example.myfirstapp.pictures.data.remote

import com.example.myfirstapp.pictures.data.Picture

data class Payload(val updatedPicture: Picture)

data class ItemEvent(val event: String, val payload: Payload)
