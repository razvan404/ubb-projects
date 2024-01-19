import android.content.Context
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import kotlinx.coroutines.channels.awaitClose
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.callbackFlow

class ProximitySensorMonitor(val context: Context) {
    val proximityValue: Flow<Float> = callbackFlow<Float> {
        val sensorManager: SensorManager =
            context.getSystemService(Context.SENSOR_SERVICE) as SensorManager
        val proximitySensor: Sensor? = sensorManager.getDefaultSensor(Sensor.TYPE_PROXIMITY)

        val proximitySensorEventListener = object : SensorEventListener {
            override fun onAccuracyChanged(sensor: Sensor, accuracy: Int) {
            }

            override fun onSensorChanged(event: SensorEvent) {
                if (event.sensor.type == Sensor.TYPE_PROXIMITY) {
                    channel.trySend(event.values[0])
                }
            }
        }

        sensorManager.registerListener(
            proximitySensorEventListener,
            proximitySensor,
            SensorManager.SENSOR_DELAY_NORMAL
        )

        awaitClose {
            sensorManager.unregisterListener(proximitySensorEventListener)
        }
    }
}
