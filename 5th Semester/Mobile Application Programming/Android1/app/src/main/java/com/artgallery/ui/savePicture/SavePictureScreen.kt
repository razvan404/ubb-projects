package com.artgallery.ui.savePicture

import android.util.Log
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.text.BasicTextField
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material3.Button
import androidx.compose.material3.CircularProgressIndicator
import androidx.compose.material3.DropdownMenu
import androidx.compose.material3.DropdownMenuItem
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.LinearProgressIndicator
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.lifecycle.viewmodel.compose.viewModel
import com.artgallery.R
import com.artgallery.core.Result
import com.artgallery.models.picture.PictureToSave
import java.lang.Integer.parseInt

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun SavePictureScreen(pictureId: String?, onClose: () -> Unit) {
    val pictureViewModel = viewModel<SavePictureViewModel>(factory = SavePictureViewModel.Factory(pictureId))
    val pictureUiState = pictureViewModel.uiState
    var title by rememberSaveable { mutableStateOf(pictureUiState.picture.title ?: "") }
    var description by rememberSaveable { mutableStateOf(pictureUiState.picture.description ?: "") }
    var typeId by rememberSaveable{ mutableIntStateOf(pictureUiState.picture.typeId ?: 0) }
    Log.d("ItemScreen", "recompose, title=$title, description=$description, typeId=$typeId")

    LaunchedEffect(pictureUiState.submitResult) {
        Log.d("ItemScreen", "Submit = ${pictureUiState.submitResult}")
        if (pictureUiState.submitResult is Result.Success) {
            Log.d("ItemScreen", "Closing screen")
            onClose()
        }
    }

    LaunchedEffect(pictureId, pictureUiState.loadResult) {
        val loadResult = pictureUiState.loadResult
        Log.d("ItemScreen", "Text initialized = ${loadResult}")
        if (loadResult is Result.Success) {
            title = loadResult.data.title
            description = loadResult.data.description ?: ""
            typeId = loadResult.data.typeId
            Log.d("ItemScreen", "Text initialized = $title, $description, $typeId")
        }
    }

    Scaffold(
        topBar = {
            TopAppBar(
                title = { Text(text = stringResource(id = if (pictureId == null) R.string.savePicture else R.string.editPicture)) },
                actions = {
                    Button(onClick = {
                        Log.d("ItemScreen", "save picture title = $title");
                        pictureViewModel.saveOrUpdateItem(title, description, typeId)
                    }) { Text("Save") }
                    Button(onClick = onClose) { Text("Close") }
                }
            )
        }
    ) {
        Column(
            modifier = Modifier
                .padding(it)
                .fillMaxSize()
        ) {
            if (pictureUiState.loadResult is Result.Loading) {
                CircularProgressIndicator()
                return@Scaffold
            }
            if (pictureUiState.submitResult is Result.Loading) {
                Column(
                    modifier = Modifier.fillMaxWidth(),
                    horizontalAlignment = Alignment.CenterHorizontally
                ) { LinearProgressIndicator() }
            }
            if (pictureUiState.loadResult is Result.Error) {
                Text(text = "Failed to load item - ${(pictureUiState.loadResult as Result.Error).exception?.message}")
            }
            Column(
                modifier = Modifier.fillMaxSize()
            ) {
                Row(
                    modifier = Modifier.padding(10.dp)
                ) {
                    Text(text = "Name")
                    Spacer(modifier = Modifier.padding(start = 8.dp))
                    TextField(
                        value = title,
                        onValueChange = { title = it },
                        modifier = Modifier
                            .weight(1f)
                            .padding(10.dp)
                            .fillMaxWidth()
                    )
                }
                Row(
                    modifier = Modifier.padding(10.dp)
                ) {
                    Text(text = "Description")
                    Spacer(modifier = Modifier.padding(start = 8.dp))
                    TextField(
                        value = description,
                        onValueChange = { description = it },
                        modifier = Modifier
                            .weight(1f)
                            .padding(10.dp)
                            .fillMaxWidth()
                    )
                }
                Row(
                    modifier = Modifier.padding(10.dp)
                ) {
                    Text(text = "Type Id")
                    Spacer(modifier = Modifier.padding(start = 8.dp))
                    TextField(
                        keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number),
                        value = typeId.toString(),
                        onValueChange = { typeId = parseInt(if (it == "") "0" else it) },
                        modifier = Modifier
                            .weight(1f)
                            .padding(10.dp)
                            .fillMaxWidth()
                    )
                }
            }
            if (pictureUiState.submitResult is Result.Error) {
                Text(
                    text = "Failed to submit item - ${(pictureUiState.submitResult as Result.Error).exception?.message}",
                    modifier = Modifier.fillMaxWidth(),
                )
            }
        }
    }
}


@Preview
@Composable
fun PreviewItemScreen() {
    SavePictureScreen(pictureId = "0", onClose = {})
}
