package com.example.myfirstapp.pictures.data.local

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.OnConflictStrategy
import androidx.room.Query
import androidx.room.Update
import com.example.myfirstapp.pictures.data.Picture
import kotlinx.coroutines.flow.Flow

@Dao
interface ItemDao {
    @Query("SELECT * FROM Pictures")
    fun getAll(): Flow<List<Picture>>

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insert(item: Picture)

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insert(items: List<Picture>)

    @Update
    suspend fun update(item: Picture): Int

    @Query("DELETE FROM Pictures WHERE _id = :id")
    suspend fun deleteById(id: String): Int

    @Query("DELETE FROM Pictures")
    suspend fun deleteAll(): Int

    @Query("DELETE FROM Pictures where title= :title and isSaved = :isSaved")
    suspend fun deletePictureNotSaved(title: String, isSaved: Boolean)

    @Query("SELECT * FROM Pictures where isSaved = :isSaved")
    suspend fun getLocalPictures(isSaved: Boolean): List<Picture>

    @Query("DELETE FROM Pictures where isSaved = :isSaved")
    suspend fun deleteNotSaved(isSaved: Boolean): Int

    @Query("SELECT COUNT(*) FROM Pictures where isSaved = :isSaved")
    suspend fun getNotSaved(isSaved: Boolean): Int
}
