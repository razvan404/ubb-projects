package com.artgallery.models.picture

import retrofit2.http.Query
import retrofit2.http.Body
import retrofit2.http.GET
import retrofit2.http.Header
import retrofit2.http.Headers
import retrofit2.http.POST
import retrofit2.http.PUT
import retrofit2.http.Path

interface PictureService {
    @GET("/api/pictures")
    suspend fun findAll(
        @Query("authorId") authorId: String
    ): List<Picture>

    @GET("/api/pictures/{id}")
    suspend fun find(
        @Path("id") id: String?
    ): Picture

    @Headers("Content-Type: application/json")
    @POST("/api/pictures")
    suspend fun create(
        @Header("Authorization") authorization: String,
        @Body picture: PictureToSave
    ): Picture

    @Headers("Content-Type: application/json")
    @PUT("/api/pictures/{id}")
    suspend fun update(
        @Header("Authorization") authorization: String,
        @Path("id") id: String?,
        @Body picture: PictureToSave
    ): Picture
}