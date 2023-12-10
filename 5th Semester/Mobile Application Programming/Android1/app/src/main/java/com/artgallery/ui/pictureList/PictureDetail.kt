package com.artgallery.ui.pictureList

import android.content.ContentValues.TAG
import android.util.Log
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.text.ClickableText
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.AnnotatedString
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.artgallery.api.Api
import com.artgallery.models.picture.Picture


@Composable
fun PictureDetail(picture: Picture, onItemClick: OnRowFn) {
    Log.d(TAG, "recompose id = ${picture.id}")

    Row(
        modifier = Modifier
            .fillMaxWidth()
            .padding(16.dp)
    ) {
        ClickableText(
            text = AnnotatedString("${picture.title} | uploaded by ${picture.author?.username ?: "no author :("} | ${Api.getImageUrl(picture.image)}"),
            style = TextStyle(
                fontSize = 24.sp,
                background = Color.White
            ),
            onClick = { _ ->
                onItemClick(picture.id)
            },
            modifier = Modifier.weight(1f)
        )
    }
}
