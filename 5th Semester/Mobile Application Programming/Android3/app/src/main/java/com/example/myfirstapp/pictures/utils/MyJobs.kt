package com.example.myfirstapp.pictures.utils

import android.app.Application
import androidx.compose.runtime.Composable
import androidx.compose.ui.platform.LocalContext
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.viewmodel.compose.viewModel
import androidx.lifecycle.viewmodel.initializer
import androidx.lifecycle.viewmodel.viewModelFactory
import androidx.work.*
import com.example.myfirstapp.MyFirstApplication
import kotlinx.coroutines.launch
import java.util.*
import java.util.concurrent.TimeUnit

//data class MyJobUiState(val isRunning: Boolean = false, val progress: Int = 0, val result: Int = 0)

class MyJobsViewModel(application: Application) : AndroidViewModel(application) {
//    var uiState by mutableStateOf(MyJobUiState())
//        private set

    private var workManager: WorkManager
    private var workId: UUID? = null

    init {
        workManager = WorkManager.getInstance(getApplication())
        startJob()
    }

    private fun startJob() {
        viewModelScope.launch {
            val constraints = Constraints.Builder()
                .setRequiredNetworkType(NetworkType.CONNECTED)
                .build()
            val inputData = Data.Builder()
//                .putInt("to", 10)
                .build()
            val myPeriodicWork = PeriodicWorkRequestBuilder<MyWorker>(1, TimeUnit.MINUTES)
            val myWork = OneTimeWorkRequest.Builder(MyWorker::class.java)
                .setConstraints(constraints)
                .setInputData(inputData)
                .build()
            workId = myWork.id
            //uiState = uiState.copy(isRunning = true)
            workManager.apply {
                // enqueue Work
                enqueue(myWork)
                // observe work status
//                getWorkInfoByIdLiveData(workId!!).asFlow().collect {
//                    Log.d("MyJobsViewModel", "$it")
////                    uiState = uiState.copy(
////                        isRunning = !it.state.isFinished,
////                        progress = it.progress.getInt("progress", 0),
////                    )
////                    if (it.state.isFinished) {
////                        uiState = uiState.copy(
////                            result = it.outputData.getInt("result", 0),
////                        )
////                    }
//                }
            }
        }
    }

    fun cancelJob() {
        workManager.cancelWorkById(workId!!)
    }

    companion object {
        fun Factory(application: Application): ViewModelProvider.Factory = viewModelFactory {
            initializer {
                val app =
                    (this[ViewModelProvider.AndroidViewModelFactory.APPLICATION_KEY] as MyFirstApplication)
                MyJobsViewModel(application)
            }
        }
    }
}

@Composable
fun MyJobs() {
    val myJobsViewModel = viewModel<MyJobsViewModel>(
        factory = MyJobsViewModel.Factory(
            LocalContext.current.applicationContext as Application
        )
    )

//    Column {
//        Text(
//            "${myJobsViewModel.uiState}",
//            style = MaterialTheme.typography.headlineSmall,
//        )
//        Button(onClick = { myJobsViewModel.cancelJob() }) {
//            Text("Cancel")
//        }
//    }
}
