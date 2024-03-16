from inference_sdk import InferenceHTTPClient
import cv2
import os
from dotenv import load_dotenv

load_dotenv()
api_key = os.getenv("API_KEY")

CLIENT = InferenceHTTPClient(
    api_url="https://detect.roboflow.com",
    api_key=api_key
)

result = CLIENT.infer("sample.jpg", model_id="ambulance-sjpea/18")

image = cv2.imread("sample.jpg")

if 'predictions' in result and result['predictions']:
    for prediction in result['predictions']:
        x, y = int(prediction['x']), int(prediction['y'])
        width, height = int(prediction['width']), int(prediction['height'])
        confidence = prediction['confidence']
        label = prediction['class']

        x1, y1 = x - width // 2, y - height // 2
        x2, y2 = x + width // 2, y + height // 2

        cv2.rectangle(image, (x1, y1), (x2, y2), (0, 255, 0), 2)

        text = f"{label}: {confidence:.2f}"
        cv2.putText(image, text, (x1, y1 - 5), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
        cv2.imshow("Inference Result", image)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

else:
    print("No detections found.")
