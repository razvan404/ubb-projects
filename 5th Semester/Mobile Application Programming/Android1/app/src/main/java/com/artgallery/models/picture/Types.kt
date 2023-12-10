package com.artgallery.models.picture

import androidx.room.Entity
import androidx.room.Ignore
import androidx.room.PrimaryKey
import androidx.room.TypeConverters
import com.artgallery.core.Converters
import com.artgallery.map.Geoloc
import com.artgallery.models.user.User
import kotlinx.serialization.Serializable
import java.util.Date

data class Photo(
    val dataUrl: String,
)

@Entity(tableName = "pictures")
@TypeConverters(Converters::class)
data class Picture(
    @PrimaryKey var id: String,
    var createdAt: Date?,
    var title: String,
    var description: String?,
    var image: String,
    @Ignore var author: User?,
    var authorId: String?,
    var typeId: Int,
    var geoloc: Geoloc?,
) {
    constructor(): this("", null, "", "", "", null, "", 0, null)
}

data class PictureEvent(val type: String, val payload: Picture)

data class PictureToSave(
    val id: String?,
    val title: String?,
    val image: String?,
    val rawImage: Photo?,
    val description: String?,
    val authorId: String?,
    val typeId: Int?,
    val geoloc: Geoloc?,
) {
    constructor(picture: Picture) : this(
        picture.id,
        picture.title,
        picture.image,
        null,
        picture.description,
        picture.authorId,
        picture.typeId,
        picture.geoloc,
    )
    constructor() : this(null, null, null, null, null, null, null, null)
}
