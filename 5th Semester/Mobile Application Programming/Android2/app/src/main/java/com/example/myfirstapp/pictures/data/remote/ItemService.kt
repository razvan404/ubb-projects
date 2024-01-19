package com.example.myfirstapp.pictures.data.remote

import com.example.myfirstapp.pictures.data.Picture
import retrofit2.http.Body
import retrofit2.http.GET
import retrofit2.http.Header
import retrofit2.http.Headers
import retrofit2.http.POST
import retrofit2.http.PUT
import retrofit2.http.Path

interface ItemService {
    @GET("/api/pictures")
    suspend fun find(@Header("Authorization") authorization: String): List<Picture>

    @GET("/api/pictures/{id}")
    suspend fun read( @Header("Authorization") authorization: String, @Path("id") itemId: String?): Picture;

    @Headers("Content-Type: application/json")
    @POST("/api/pictures")
    suspend fun create(@Header("Authorization") authorization: String, @Body picture: Picture): Picture

    @Headers("Content-Type: application/json")
    @PUT("/api/pictures/{id}")
    suspend fun update( @Header("Authorization") authorization: String, @Path("id") itemId: String?, @Body picture: Picture): Picture
}
