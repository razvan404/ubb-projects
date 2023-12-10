package com.artgallery.models.picture

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.OnConflictStrategy
import androidx.room.Query
import androidx.room.Update
import kotlinx.coroutines.flow.Flow

@Dao
interface PictureDao {
    @Query("SELECT * FROM Pictures")
    fun getAll(): Flow<List<Picture>>

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insert(item: Picture)

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertMany(items: List<Picture>)

    @Update
    suspend fun update(item: Picture): Int

    @Query("DELETE FROM Pictures WHERE id = :id")
    suspend fun deleteById(id: String): Int

    @Query("DELETE FROM Pictures")
    suspend fun deleteAll()
}