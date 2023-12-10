package com.artgallery.core

import androidx.room.TypeConverter
import com.artgallery.map.Geoloc
import java.lang.Float.parseFloat
import java.util.Date

class Converters {
    @TypeConverter
    fun fromTimestamp(value: Long?): Date? {
        return value?.let { Date(it) }
    }

    @TypeConverter
    fun dateToTimestamp(date: Date?): Long? {
        return date?.time?.toLong()
    }

    @TypeConverter
    fun fromGeoloc(value: String?): Geoloc? {
        return value?.let { str -> str.split(',').let { Geoloc(parseFloat(it[0]), parseFloat(it[1])) } }
    }

    @TypeConverter
    fun geolocToString(geoloc: Geoloc?): String? {
        return geoloc?.let { "${geoloc.lat},${geoloc.lng}" }
    }
}