import gradio
import torch
import torchvision.transforms as transforms
import cv2
import numpy as np

from core.config import load_config


CROP_SIZE = 600


def binary_predictions(raw_preds: torch.Tensor) -> torch.Tensor:
    return (torch.sigmoid(raw_preds) >= 0.5).float()


def crop_image_function_creator(shape: int):
    return lambda x: x[
        (x.shape[0] - shape) // 2 : (x.shape[0] + shape) // 2,
        (x.shape[1] - shape) // 2 : (x.shape[1] + shape) // 2,
        :,
    ]


def blur_background(input_image):
    # Generate a blank mask
    image_tensor = preprocess(input_image).unsqueeze(0)
    mask = binary_predictions(model(image_tensor)).numpy()[0].transpose(1, 2, 0)

    input_image = cv2.resize(
        crop_image_function_creator(CROP_SIZE)(input_image), mask.shape[:2]
    )

    # apply a strong Gaussian blur to the areas outside the mask
    # blurred = cv2.GaussianBlur(input_image, (51, 51), 0)
    yellow_mask = (np.full(input_image.shape, [255, 255, 0]) * 2 + input_image * 3) // 5
    result = np.where(mask, yellow_mask, input_image)

    return result


if __name__ == "__main__":
    config = load_config("demo")
    model = torch.jit.load(config["model_path"]).cpu()

    preprocess = transforms.Compose(
        [
            transforms.Lambda(crop_image_function_creator(CROP_SIZE)),
            transforms.ToTensor(),
            transforms.Normalize(mean=[0.5, 0.5, 0.5], std=[0.5, 0.5, 0.5]),
            transforms.transforms.Resize((240, 240), antialias=True),
        ]
    )

ui = gradio.Interface(
    fn=blur_background,
    inputs=gradio.Image(sources=["webcam"], streaming=True),
    outputs="image",
    # live=True,
    title="Image segmentation demo",
    allow_flagging="never",
)
ui.dependencies[0]["show_progress"] = False
ui.launch()
