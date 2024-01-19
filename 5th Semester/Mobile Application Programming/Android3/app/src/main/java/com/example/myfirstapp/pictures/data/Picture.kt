package com.example.myfirstapp.pictures.data

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "pictures")
data class Picture(@PrimaryKey var _id: String = "",
                   val title: String = "",
                   val description: String = "",
                   val imageUrl: String="",
                   val dateOfRelease: String="",
                   val isPhotography: Boolean=false,
                   var isSaved: Boolean=true,
                   var lat: Double=0.0,
                   var lon: Double=0.0)
