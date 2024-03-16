from inference_sdk import InferenceHTTPClient
import cv2
import concurrent.futures
from dotenv import load_dotenv

load_dotenv()
api_key = os.getenv("API_KEY")

CLIENT = InferenceHTTPClient(
    api_url="https://detect.roboflow.com",
    api_key=api_key
)

def process_frame(frame):
    gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    result = CLIENT.infer(gray_frame, model_id="ambulance-sjpea/18")

    if 'predictions' in result and result['predictions']:
        for prediction in result['predictions']:
            x, y = int(prediction['x']), int(prediction['y'])
            width, height = int(prediction['width']), int(prediction['height'])
            confidence = prediction['confidence']
            label = prediction['class']

            x1, y1 = x - width // 2, y - height // 2
            x2, y2 = x + width // 2, y + height // 2

            cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)

            text = f"{label}: {confidence:.2f}"
            cv2.putText(frame, text, (x1, y1 - 5), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

    return frame

video_path = "amb.mp4"
cap = cv2.VideoCapture(video_path)

if not cap.isOpened():
    print("Error: Could not open video file.")
    exit()

while True:
    ret, frame = cap.read()

    if not ret:
        break

    with concurrent.futures.ThreadPoolExecutor() as executor:
        future = executor.submit(process_frame, frame)

        processed_frame = future.result()

    cv2.imshow("Inference Result", processed_frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
