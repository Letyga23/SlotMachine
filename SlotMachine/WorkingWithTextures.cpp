#include "WorkingWithTextures.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//Хэш-карта для хранения текстур по индексам
std::map<int, GLuint> WorkingWithTextures::textureCache;

//Массив с путями к изображениям (ресурсы для использования в игре)
const char* WorkingWithTextures::resourceNames[] =
{
    "Image\\cherry.png",   //IDB_PNG1
    "Image\\clover.png",   //IDB_PNG2
    "Image\\diamond.png",  //IDB_PNG3
    "Image\\grape.png",    //IDB_PNG4
    "Image\\heart.png",    //IDB_PNG5
    "Image\\lemon.png",    //IDB_PNG6
    "Image\\seven.png"     //IDB_PNG7
};

int WorkingWithTextures::getCountTexture()
{
    return sizeof(resourceNames) / sizeof(resourceNames[0]);
}

//Функция для загрузки текстуры из файла
GLuint WorkingWithTextures::loadTexture(const char* filename)
{
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);  //Загружаем изображение

    if (!data)
    {
        DebugLog("Failed to load texture!"); 
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);  //Генерирация текстур
    glBindTexture(GL_TEXTURE_2D, textureID);  //Привязываем текстуру

    //Устанавка параметров текстур
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Загрузка текстуры в OpenGL в зависимости от количества каналов
    if (nrChannels == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);  

    stbi_image_free(data);  //Освобождение памяти

    return textureID;
}

//Функция для загрузки текстуры из ресурсов
GLuint WorkingWithTextures::loadTextureFromResource(HINSTANCE hInstance, int index)
{
    //Проверка на корректность индекса
    if (index < 0 || index >= getCountTexture())
    {
        DebugLog("Index out of bounds!"); 
        return 0;
    }

    const char* resourcePath = resourceNames[index];  //Путь к ресурсу
    HRSRC hResource = FindResource(hInstance, MAKEINTRESOURCE(index + 101), L"PNG");  //Находим ресурс

    if (!hResource)
    {
        DebugLog("Failed to find resource!"); 
        return 0;
    }

    HGLOBAL hLoadedResource = LoadResource(hInstance, hResource);  //Загружаем ресурс
    if (!hLoadedResource)
    {
        DebugLog("Failed to load resource!");  //Если не удалось загрузить ресурс
        return 0;
    }

    void* pData = LockResource(hLoadedResource);  //Получаем данные ресурса
    DWORD dwSize = SizeofResource(hInstance, hResource);  //Получаем размер ресурса

    int width, height, nrChannels;
    unsigned char* data = stbi_load_from_memory((unsigned char*)pData, dwSize, &width, &height, &nrChannels, 0);  //Загружаем данные изображения из памяти

    if (!data)
    {
        DebugLog("Failed to load image data from resource!"); 
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);  //Генерирация текстур
    glBindTexture(GL_TEXTURE_2D, textureID);  //Привязываем текстуру

   //Устанавка параметров текстур
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Загрузка текстуры в OpenGL в зависимости от количества каналов
    if (nrChannels == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D); 

    stbi_image_free(data);  

    return textureID;
}

//Функция для отрисовки текстуры
void WorkingWithTextures::drawTexture(GLuint textureID, float x, float y, float width, float height)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);  //Включаем использование текстуры
    glBindTexture(GL_TEXTURE_2D, textureID);  //Привязываем текстуру

    glBegin(GL_TRIANGLE_STRIP);  //Рисуем прямоугольник с текстурой
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y + height);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y + height);
    glEnd();

    glDisable(GL_TEXTURE_2D);  //Выключаем использование текстуры
}

void WorkingWithTextures::deleteTexture(GLuint textureID)
{
    glDeleteTextures(1, &textureID);
}

GLuint WorkingWithTextures::getTextureFromCache(HINSTANCE hInstance, int index)
{
    if (textureCache.find(index) != textureCache.end())
    {
        return textureCache[index];  //Возвращаем кэшированную текстуру
    }

    GLuint textureID = loadTextureFromResource(hInstance, index);
    if (textureID != 0)
    {
        textureCache[index] = textureID;  //Кэшируем текстуру
    }
    return textureID;
}