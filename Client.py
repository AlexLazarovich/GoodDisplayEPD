import cv2
import numpy as np
import requests

# ESP32 server URL
esp32_url_set_length = 'http://192.168.0.81/setLength'  # URL for setting the length
esp32_url_upload = 'http://192.168.0.81/upload'  # URL for uploading the image data

# GDEPD color codes
color_map = {
    (0, 0, 0): 0x00,  # Black
    (255, 255, 255): 0x01,  # White
    (0, 255, 0): 0x06,  # Green
    (0, 0, 255): 0x05,  # Blue
    (255, 0, 0): 0x03,  # Red
    (255, 255, 0): 0x02,  # Yellow
    (127, 127, 127): 0x07  # Clean
}

def color_to_gdepd_code(color):
    # Calculate the Euclidean distance between the color and each color in the map
    distances = {k: np.linalg.norm(np.array(k) - np.array(color)) for k in color_map.keys()}
    # Find the key (color) with the minimum distance
    closest_color = min(distances, key=distances.get)
    return color_map[closest_color]

def process_image(image_path, width=800, height=480):
    # Load the image
    image = cv2.imread(image_path)

    # Calculate the aspect ratio
    h, w = image.shape[:2]
    aspect_ratio = w / h

    # Determine the new size to maintain aspect ratio
    if aspect_ratio > width / height:
        new_width = width
        new_height = int(width / aspect_ratio)
    else:
        new_height = height
        new_width = int(height * aspect_ratio)

    # Resize the image to the new size
    resized_image = cv2.resize(image, (new_width, new_height))

    # Create a white canvas
    canvas = np.ones((height, width, 3), dtype=np.uint8) * 255

    # Center the resized image on the canvas
    x_offset = (width - new_width) // 2
    y_offset = (height - new_height) // 2
    canvas[y_offset:y_offset+new_height, x_offset:x_offset+new_width] = resized_image

    # Convert the image colors to GDEPD color codes
    color_coded_image = np.zeros((height, width), dtype=np.uint8)
    for y in range(height):
        for x in range(width):
            color = canvas[y, x]
            gdepd_code = color_to_gdepd_code(color)
            color_coded_image[y, x] = gdepd_code

    return color_coded_image

def encode_image(image_array):
    encoded_image = []
    current_color = image_array[0][0]
    count = 0

    for y in range(image_array.shape[0]):
        for x in range(image_array.shape[1]):
            # print(image_array[y][x] )
            if image_array[y][x] == current_color:
                count += 1
                if count == 31:  # Maximum count value that can be stored in 5 bits
                    encoded_image.append((count << 3) | current_color)
                    count = 0
            else:
                if count > 0:
                    encoded_image.append((count << 3) | current_color)
                current_color = image_array[y][x]
                count = 1

    if count > 0:
        encoded_image.append((count << 3) | current_color)

    return encoded_image

def send_image_to_esp32(encoded_image):
    # Convert the encoded image list to bytes
    image_bytes = bytes(encoded_image)
    
    # Print the number of bytes
    print(f"Encoded image size: {len(image_bytes)} bytes")
    
    # Send the length of the encoded image to the ESP32
    length_response = requests.post(esp32_url_set_length, data=str(len(image_bytes)))
    print(f"Set length response: {length_response.text}")

    # Send the image bytes to the ESP32
    response = requests.post(esp32_url_upload, data=image_bytes)
    print(response.text)

if __name__ == '__main__':
    # Image file path
    image_path = 'logo_icvl.png'  # Replace with the path to your image

    # Process the image
    processed_image = process_image(image_path)

    # Encode the processed image
    encoded_image = encode_image(processed_image)

    # Send the encoded image to the ESP32
    send_image_to_esp32(encoded_image)
