
#include "Image_Class.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

// filter 1
void gray_scale(Image &image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            int avg = 0;
            for (int k = 0; k < image.channels; k++)
            {
                avg += image(i, j, k);
            }
            avg /= image.channels;
            for (int k = 0; k < image.channels; k++)
            {
                image(i, j, k) = avg;
            }
        }
    }
}

// Filter 2
void BandW(Image &img)
{
    for (int x = 0; x < img.width; x++)
    {
        for (int y = 0; y < img.height; y++)
        {
            int r = img(x, y, 0);
            int g = img(x, y, 1);
            int b = img(x, y, 2);
            double gray = 0.3 * r + 0.59 * g + 0.11 * b;
            unsigned char bw = (gray >= 128) ? 255 : 0;
            for (int z = 0; z < img.channels; z++)
            {
                img(x, y, z) = bw;
            }
        }
    }
}

// filter 3
Image invertColors(const Image &img)
{
    Image inverted(img.width, img.height);
    for (int x = 0; x < img.width; ++x)
    {
        for (int y = 0; y < img.height; ++y)
        {
            for (int c = 0; c < img.channels; ++c)
            {
                inverted(x, y, c) = 255 - img(x, y, c);
            }
        }
    }
    return inverted;
}
// Filter 4
Image merge_images(Image &image1) {
    string filename_2;
    cout << "Pls enter second image path: ";
    cin >> filename_2;

    Image image2(filename_2);

    if (!image2.imageData) {
        cerr << "Failed to load second image!" << endl;
        return image1; 
    }


    Image new_image(image2.width, image2.height);

    new_image.channels = image1.channels; 

    for (int i = 0; i < new_image.width; i++) {
        for (int j = 0; j < new_image.height; j++) {
            for (int k = 0; k < new_image.channels; k++) {
                new_image(i, j, k) =
                    image1(int(i * double(image1.width) / new_image.width),
                           int(j * double(image1.height) / new_image.height), k);
            }
        }
    }

    
    for (int i = 0; i < new_image.width; i++) {
        for (int j = 0; j < new_image.height; j++) {
            for (int k = 0; k < new_image.channels; k++) {
                new_image(i, j, k) =
                    (image2(i, j, k) + new_image(i, j, k)) / 2;
            }
        }
    }

    return new_image;
}

// Filter 5
void flipH(Image &img)
{
    for (int x = 0; x < img.width / 2; x++)
    {
        for (int y = 0; y < img.height; y++)
        {
            for (int z = 0; z < img.channels; z++)
            {
                unsigned char temp = img(x, y, z);
                img(x, y, z) = img(img.width - 1 - x, y, z);
                img(img.width - 1 - x, y, z) = temp;
            }
        }
    }
}
void flipV(Image &img)
{
    for (int x = 0; x < img.width; x++)
    {
        for (int y = 0; y < img.height / 2; y++)
        {
            for (int z = 0; z < img.channels; z++)
            {
                unsigned char temp = img(x, y, z);
                img(x, y, z) = img(x, img.height - 1 - y, z);
                img(x, img.height - 1 - y, z) = temp;
            }
        }
    }
}

// filter 6
void rotate90(Image &img)
{
    Image rotated(img.height, img.width);
    for (int i = 0; i < img.width; ++i)
        for (int j = 0; j < img.height; ++j)
            for (int k = 0; k < img.channels; ++k)
                rotated(j, img.width - 1 - i, k) = img(i, j, k);
    img = rotated;
}
void rotate180(Image &img)
{
    Image rotated(img.width, img.height);
    for (int i = 0; i < img.width; ++i)
        for (int j = 0; j < img.height; ++j)
            for (int k = 0; k < img.channels; ++k)
                rotated(img.width - 1 - i, img.height - 1 - j, k) = img(i, j, k);
    img = rotated;
}
void rotate270(Image &img)
{
    Image rotated(img.height, img.width);
    for (int i = 0; i < img.width; ++i)
        for (int j = 0; j < img.height; ++j)
            for (int k = 0; k < img.channels; ++k)
                rotated(img.height - 1 - j, i, k) = img(i, j, k);
    img = rotated;
}

// filter 7
void LightDark(Image &img, float factor)
{
    for (int x = 0; x < img.width; x++)
    {
        for (int y = 0; y < img.height; y++)
        {
            for (int z = 0; z < img.channels; z++)
            {
                int value = static_cast<int>(img(x, y, z) * factor);
                if (value > 255)
                    value = 255;
                if (value < 0)
                    value = 0;
                img(x, y, z) = static_cast<unsigned char>(value);
            }
        }
    }
}
// filter 8
void crop(Image &img, int startX, int startY, int cropWidth, int cropHeight) {
    if (startX < 0 || startY < 0) {
        cout << "Starting point cannot be negative." << endl;
        return;
    }
    if (cropWidth > img.width - startX || cropHeight > img.height - startY) {
        cout << "Crop size is too large for the given starting point." << endl;
        return;
    }

    Image cropped(cropWidth, cropHeight);

    for (int x = 0; x < cropWidth; x++) {
        for (int y = 0; y < cropHeight; y++) {
            for (int z = 0; z < img.channels; z++) {
                cropped(x, y, z) = img(x + startX, y + startY, z);
            }
        }
    }

    img = cropped;
}

// filter 9
void addWhiteFrame(Image &image, int thickness, string style)
{
    unsigned char r = 255, g = 255, b = 255; // white color
    for (int x = 0; x < image.width; ++x)
    {
        for (int y = 0; y < thickness; ++y)
        {
            if (style == "dotted" && (x + y) % 2 != 0)
                continue;

            image(x, y, 0) = r;
            image(x, y, 1) = g;
            image(x, y, 2) = b;

            image(x, image.height - 1 - y, 0) = r;
            image(x, image.height - 1 - y, 1) = g;
            image(x, image.height - 1 - y, 2) = b;
        }
    }

    for (int y = 0; y < image.height; ++y)
    {
        for (int x = 0; x < thickness; ++x)
        {
            if (style == "dotted" && (x + y) % 2 != 0)
                continue;

            image(x, y, 0) = r;
            image(x, y, 1) = g;
            image(x, y, 2) = b;

            image(image.width - 1 - x, y, 0) = r;
            image(image.width - 1 - x, y, 1) = g;
            image(image.width - 1 - x, y, 2) = b;
        }
    }
}
// filter 10
Image detect_image_edges(Image &image) {
    Image img = image; 
    gray_scale(img);
    BandW(img); 

    int width = img.width;
    int height = img.height;
    Image edges(width, height);

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            int Gx = img(x + 1, y, 0) - img(x - 1, y, 0);
            int Gy = img(x, y + 1, 0) - img(x, y - 1, 0);

            if (abs(Gx) + abs(Gy) > 128) {
                edges(x, y, 0) = edges(x, y, 1) = edges(x, y, 2) = 0;
            } else {
                edges(x, y, 0) = edges(x, y, 1) = edges(x, y, 2) = 255;
            }
        }
    }

    return edges;
}
//filter 11
void resizeImage(Image &img, int newWidth, int newHeight) {
    Image resized(newWidth, newHeight);

    float xRatio = (float)img.width / newWidth;
    float yRatio = (float)img.height / newHeight;

    for (int x = 0; x < newWidth; x++) {
        for (int y = 0; y < newHeight; y++) {
            int origX = int(x * xRatio);
            int origY = int(y * yRatio);
            for (int z = 0; z < img.channels; z++) {
                resized(x, y, z) = img(origX, origY, z);
            }
        }
    }

    img = resized;
}

// filter 12
void applyBoxBlur(Image &image, int blurLevel)
{
    int kernelSize = 2 * blurLevel + 1;
    int halfKernel = blurLevel;
    Image temp = image; // Copy for reading original pixels

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int sum[3] = {0, 0, 0};
            int count = 0;

            for (int dx = -halfKernel; dx <= halfKernel; ++dx)
            {
                for (int dy = -halfKernel; dy <= halfKernel; ++dy)
                {
                    int x = i + dx;
                    int y = j + dy;

                    if (x >= 0 && x < image.width && y >= 0 && y < image.height)
                    {
                        for (int k = 0; k < 3; ++k)
                        {
                            sum[k] += temp(x, y, k);
                        }
                        ++count;
                    }
                }
            }

            for (int k = 0; k < 3; ++k)
            {
                image(i, j, k) = sum[k] / count;
            }
        }
    }
}

int main()
{
    string filename;
    cout << "Enter the filename of the image: ";
    cin >> filename;
    Image originalImg(filename);

    if (!originalImg.imageData)
    {
        cerr << "Failed to load image, Please use .bmp, .jpg, .jpeg, or .png: " << filename << endl;
        return -1;
    }
    while (true)
    {
        cout << "\nmenu\n";
        cout << "choose a filter to apply or 0 to exit:\n";
        cout << "0-Exit\n";
        cout << "1-Grayscale\n";
        cout << "2-Black and White\n";
        cout << "3-Invert Image\n";
        cout << "4- Merge Images\n"; 
        cout << "5-Flipping Image\n";
        cout << "6-Rotate Image\n";
        cout << "7-Lighten/Darken\n";
        cout << "8- Crop Image\n";
        cout << "9- Blur Images\n";
        cout << "10- Detect Image Edges\n";
        cout << "11- Resize Image\n";
        cout << "12- Adding a Frame to the Picture\n";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 0:
            cout << "Exiting the program.\n";
            return 0;
        case 1:
        {
            Image img = originalImg;
            gray_scale(img);
            cout << "Grayscale filter applied.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string saveFile;
            cout << "Enter filename to save the image or press Enter to skip: ";
            getline(cin, saveFile);
            if (!saveFile.empty())
            {
                img.saveImage(saveFile);
                cout << "Image saved as " << saveFile << "\n";
            }
            break;
        }
        case 2:
        {
            Image img = originalImg;
            BandW(img);
            cout << "Black and White filter applied.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string saveFile;
            cout << "Enter filename to save the image or press Enter to skip: ";
            getline(cin, saveFile);
            if (!saveFile.empty())
            {
                img.saveImage(saveFile);
                cout << "Image saved as " << saveFile << "\n";
            }
            break;
        }

        case 3:
        {
            Image img = originalImg;
            img = invertColors(img);
            cout << "Invert Image filter applied.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string saveFile;
            cout << "Enter filename to save the image or press Enter to skip: ";
            getline(cin, saveFile);
            if (!saveFile.empty())
            {
                img.saveImage(saveFile);
                cout << "Image saved as " << saveFile << "\n";
            }
            break;
        }
         case 4: {
                Image img = originalImg;
                img = merge_images(img);
                cout << "Merge Images filter applied.\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string saveFile;
                cout << "Enter filename to save the image or press Enter to skip: ";
                getline(cin, saveFile);
                if (!saveFile.empty()) {
                    img.saveImage(saveFile);
                    cout << "Image saved as " << saveFile << "\n";
                }
                break;
            } 
            
        case 5:
        {
            Image img = originalImg;
            cout << "if u want to flip horizontal press 1, if u want to flip vertical press 2\n";
            int whichflip;
            cin >> whichflip;

            if (whichflip == 1)
            {
                flipH(img);
                cout << "Image flipped horizontally.\n";
            }
            else if (whichflip == 2)
            {
                flipV(img);
                cout << "Image flipped vertically.\n";
            }
            else
            {
                cout << "Invalid choice for flip direction.\n";
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string saveFile;
            cout << "Enter filename to save the image or press Enter to skip: ";
            getline(cin, saveFile);
            if (!saveFile.empty())
            {
                img.saveImage(saveFile);
                cout << "Image saved as " << saveFile << "\n";
            }
            break;
        }

        case 6:
        {
            Image img = originalImg;
            int angle;
            cout << "Enter rotation angle (90, 180, 270): ";
            cin >> angle;
            if (angle == 90)
            {
                rotate90(img);
            }
            else if (angle == 180)
            {
                rotate180(img);
            }
            else if (angle == 270)
            {
                rotate270(img);
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string saveFile;
            cout << "Enter filename to save the image or press Enter to skip: ";
            getline(cin, saveFile);
            if (!saveFile.empty())
            {
                img.saveImage(saveFile);
                cout << "Image saved as " << saveFile << "\n";
            }
            break;
        }
        case 7:
        {
            Image img = originalImg;
            float factor;
            cout << "Enter factor (e.g. >1 to lighten, <1 to darken): ";
            cin >> factor;
            LightDark(img, factor);
            cout << "Lighten/Darken filter applied.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string saveFile;
            cout << "Enter filename to save the image or press Enter to skip: ";
            getline(cin, saveFile);
            if (!saveFile.empty())
            {
                img.saveImage(saveFile);
                cout << "Image saved as " << saveFile << "\n";
            }
            break;
        }
        case 8: {
                Image img = originalImg;

                int startX, startY, cropWidth, cropHeight;
                cout << "Enter starting X coordinate: ";
                cin >> startX;
                cout << "Enter starting Y coordinate: ";
                cin >> startY;
                cout << "Enter width of crop: ";
                cin >> cropWidth;
                cout << "Enter height of crop: ";
                cin >> cropHeight;

                crop(img, startX, startY, cropWidth, cropHeight);
                cout << "Image cropped.\n";

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string saveFile;
                cout << "Enter filename to save the image or press Enter to skip: ";
                getline(cin, saveFile);
                if (!saveFile.empty()) {
                    img.saveImage(saveFile);
                    cout << "Image saved as " << saveFile << "\n";
                }
                break;
            }
        
        case 9:
        {
            int blurLevel;
            cout << "Enter blur level (e.g., 1 to 5): ";
            cin >> blurLevel;
            Image img = originalImg;
            applyBoxBlur(img, blurLevel);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string saveFile;
            cout << "Enter filename to save the image or press Enter to skip: ";
            getline(cin, saveFile);
            if (!saveFile.empty())
            {
                img.saveImage(saveFile);
                cout << "Image saved as " << saveFile << "\n";
            }
            break;
        }
             case 10:{
                Image img = detect_image_edges(originalImg);
                cout << "Detect Image Edges filter applied.\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string saveFile;
                cout << "Enter filename to save the image or press Enter to skip: ";
                getline(cin, saveFile);
                if (!saveFile.empty()) {
                    img.saveImage(saveFile);
                    cout << "Image saved as " << saveFile << "\n";
                }
                break;
            }
         case 11: {
                Image img = originalImg;
                int newWidth, newHeight;
                cout << "Enter new width: ";
                cin >> newWidth;
                cout << "Enter new height: ";
                cin >> newHeight;

                resizeImage(img, newWidth, newHeight);
                cout << "Image resized.\n";

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string saveFile;
                cout << "Enter filename to save the image or press Enter to skip: ";
                getline(cin, saveFile);
                if (!saveFile.empty()) {
                img.saveImage(saveFile);
                cout << "Image saved as " << saveFile << "\n";
                }
                break;
            }

        case 12:
        {
            int thickness;
            string style;
            cout << "Enter frame style (simple or dotted): ";
            cin >> style;
            cout << "Enter frame thickness in pixels: ";
            cin >> thickness;

            Image img = originalImg;
            addWhiteFrame(img, thickness, style);

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string saveFile;
            cout << "Enter filename to save the image or press Enter to skip: ";
            getline(cin, saveFile);
            if (!saveFile.empty())
            {
                img.saveImage(saveFile);
                cout << "Image saved as " << saveFile << "\n";
            }
            break;
        }

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
    return 0;
}