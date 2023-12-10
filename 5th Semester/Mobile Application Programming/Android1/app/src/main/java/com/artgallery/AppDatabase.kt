package com.artgallery

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import com.artgallery.models.picture.Picture
import com.artgallery.models.picture.PictureDao

@Database(entities = [Picture::class], version = 1)
abstract class AppDatabase : RoomDatabase() {
    abstract fun pictureDao(): PictureDao

    companion object {
        @Volatile
        private var INSTANCE: AppDatabase? = null

        fun getDatabase(context: Context): AppDatabase {
            return INSTANCE ?: synchronized(this) {
                val instance = Room.databaseBuilder(
                    context,
                    AppDatabase::class.java,
                    "app_database"
                )
                    .build()
                INSTANCE = instance
                instance
            }
        }
    }
}
