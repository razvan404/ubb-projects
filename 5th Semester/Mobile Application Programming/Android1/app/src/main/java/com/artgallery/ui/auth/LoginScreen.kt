package com.artgallery.ui.auth

import android.util.Log
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.LinearProgressIndicator
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.input.PasswordVisualTransformation
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.lifecycle.viewmodel.compose.viewModel
import com.artgallery.R
import com.artgallery.core.TAG

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun LoginScreen(onClose: () -> Unit) {
    val loginViewModel = viewModel<LoginViewModel>(factory = LoginViewModel.Factory)
    val loginUiState = loginViewModel.uiState

    Scaffold(
        topBar = { TopAppBar(
            title = { Text(text = stringResource(id = R.string.login)) })}
    ) {
        Column(
            modifier = Modifier
                .padding(it)
                .fillMaxSize()
                .padding(24.dp)
        ) {
            var usernameOrEmail by remember { mutableStateOf("") }
            TextField(
                label = { Text(text = "Username or Email") },
                value = usernameOrEmail,
                onValueChange = { usernameOrEmail = it },
                modifier = Modifier.fillMaxWidth()
            )
            var password by remember { mutableStateOf("") }
            TextField(
                label = { Text(text = "Password") },
                visualTransformation = PasswordVisualTransformation(),
                value = password,
                onValueChange = { password = it },
                modifier = Modifier.fillMaxWidth()
            )
            Log.d(TAG, "recompose");
            Button(onClick = {
                Log.d(TAG, "login...");
                loginViewModel.login(usernameOrEmail, password)
            }) {
                Text("Login")
            }
            if (loginUiState.isAuthenticating) {
                LinearProgressIndicator(
                    modifier = Modifier
                        .fillMaxWidth()
                        .height(15.dp)
                );
            }
            if (loginUiState.authenticationError != null) {
                Text(text = "Login failed ${loginUiState.authenticationError.message}")
            }
        }
    }

    LaunchedEffect(loginUiState.authenticationCompleted) {
        Log.d(TAG, "Auth completed");
        if (loginUiState.authenticationCompleted) {
            onClose();
        }
    }
}

@Preview(showBackground = true)
@Composable
fun LoginScreenPreview() {
    LoginScreen({})
}