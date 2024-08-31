import os
import glob
import gradio

from dataloader import build_image_transform
from utils import save_model_to_binaries, load_binaries, binary_predictions


def load_model(model_name):
    model_path = os.path.join("binaries", f"{model_name}.pt")
    if not os.path.exists(model_path):
        files = glob.glob(f'saved_models/{model_name}/checkpoint_*.pt')
        path = max(files, key=os.path.getctime)
        save_model_to_binaries(path, model_path)
    return load_binaries(model_path)


model = load_model("ad504ec7-53db-4096-970d-66249dbcf502").to('cuda')
model.eval()


def predict(image):
    image_transform = build_image_transform(size=(720, 1280))
    transformed_image = image_transform(image)
    image = transformed_image.unsqueeze(0).to('cuda')
    mask = binary_predictions(model(image)).squeeze().cpu()
    return mask.detach().numpy()


ui = gradio.Interface(
    fn=predict,
    inputs=gradio.Image(sources=["upload"]),
    outputs="image",
    title="Forest Fire Segmentation",
    allow_flagging="never"
)
ui.launch(share=True)
