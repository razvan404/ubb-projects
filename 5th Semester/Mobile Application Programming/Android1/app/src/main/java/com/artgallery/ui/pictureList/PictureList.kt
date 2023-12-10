package com.artgallery.ui.pictureList

import android.content.ContentValues.TAG
import android.util.Log
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import com.artgallery.models.picture.Picture

typealias OnRowFn = (id: String?) -> Unit

@Composable
fun PictureList(picturesList: List<Picture>, onRowClick: OnRowFn, modifier: Modifier) {
    Log.d(TAG, "recompose")
    LazyColumn(
        modifier = modifier
            .fillMaxSize()
            .padding(12.dp)
    ) {
        items(picturesList) { picture ->
            PictureDetail(picture, onRowClick)
        }
    }
}

