from keras.models import Sequential
from keras.layers import Dense, Conv2D, Flatten, Dropout, MaxPooling2D, BatchNormalization


def get_cnn_classifier(outputs_count: int = 2, images_size: tuple[int, int] = (64, 64)):
    model = Sequential()
    model.add(Conv2D(32, 3, padding="same", activation="relu", input_shape=(images_size[0], images_size[1], 3)))
    # model.add(BatchNormalization())
    model.add(MaxPooling2D())
    model.add(Conv2D(64, 3, padding="same", activation="relu"))
    # model.add(BatchNormalization())
    model.add(MaxPooling2D())
    model.add(Dropout(0.4))
    model.add(Flatten())
    model.add(Dense(outputs_count, activation="softmax"))
    model.compile(optimizer="adam", loss="sparse_categorical_crossentropy", metrics=['accuracy'])

    # Print the model summary
    model.summary()
    
    return model
