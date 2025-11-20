#include "sprite.h"
#include <windows.h>
#include <cstdio>

// Construtor - inicializa variáveis
Sprite::Sprite()
    : m_bitmap(nullptr)
    , m_width(0)
    , m_height(0)
{
}

// Destrutor - limpa recursos
Sprite::~Sprite() {
    if (m_bitmap) {
        DeleteObject(m_bitmap);
        m_bitmap = nullptr;
    }
}

// Carrega imagem BMP do arquivo (carregamento manual)
bool Sprite::LoadFromFile(const char* filename) {
    // Limpar bitmap anterior se existir
    if (m_bitmap) {
        DeleteObject(m_bitmap);
        m_bitmap = nullptr;
    }
    
    // Abrir arquivo
    FILE* file = fopen(filename, "rb");
    if (!file) {
        m_width = 0;
        m_height = 0;
        return false;
    }
    
    // Ler headers do BMP
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    
    if (fread(&bf, sizeof(BITMAPFILEHEADER), 1, file) != 1) {
        fclose(file);
        return false;
    }
    
    if (fread(&bi, sizeof(BITMAPINFOHEADER), 1, file) != 1) {
        fclose(file);
        return false;
    }
    
    // Verificar se é BMP válido (assinatura "BM" = 0x4D42)
    if (bf.bfType != 0x4D42) {
        fclose(file);
        m_width = 0;
        m_height = 0;
        return false;
    }
    
    // Calcular tamanho da imagem se não especificado
    if (bi.biSizeImage == 0) {
        bi.biSizeImage = ((bi.biWidth * bi.biBitCount + 31) / 32) * 4 * abs(bi.biHeight);
    }
    
    // Criar estrutura BITMAPINFO
    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(BITMAPINFO));
    bmi.bmiHeader = bi;
    
    // Criar bitmap usando CreateDIBSection
    HDC screenDC = GetDC(nullptr);
    void* bits = nullptr;
    
    m_bitmap = CreateDIBSection(
        screenDC,
        &bmi,
        DIB_RGB_COLORS,
        &bits,
        nullptr,
        0
    );
    
    if (!m_bitmap || !bits) {
        ReleaseDC(nullptr, screenDC);
        fclose(file);
        m_width = 0;
        m_height = 0;
        return false;
    }
    
    // Ler dados do bitmap do arquivo
    fseek(file, bf.bfOffBits, SEEK_SET);
    if (fread(bits, bi.biSizeImage, 1, file) != 1) {
        DeleteObject(m_bitmap);
        m_bitmap = nullptr;
        ReleaseDC(nullptr, screenDC);
        fclose(file);
        m_width = 0;
        m_height = 0;
        return false;
    }
    
    m_width = bi.biWidth;
    m_height = abs(bi.biHeight);
    
    ReleaseDC(nullptr, screenDC);
    fclose(file);
    
    return true;
}

//Cria bitmap de teste programaticamente
bool Sprite::CreateTestBitmap(int width, int height) {
    //Limpar bitmap anterior se existir
    if (m_bitmap) {
        DeleteObject(m_bitmap);
        m_bitmap = nullptr;
    }
    
    //Criar bitmap compatível com a tela
    HDC screenDC = GetDC(nullptr);
    if (!screenDC) {
        return false;
    }
    
    HDC memDC = CreateCompatibleDC(screenDC);
    if (!memDC) {
        ReleaseDC(nullptr, screenDC);
        return false;
    }
    
    //Criar bitmap
    m_bitmap = CreateCompatibleBitmap(screenDC, width, height);
    if (!m_bitmap) {
        DeleteDC(memDC);
        ReleaseDC(nullptr, screenDC);
        return false;
    }
    
    //Selecionar bitmap no DC
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, m_bitmap);
    
    //Desenhar padrão colorido (gradiente)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            //Criar gradiente de cores
            int r = (x * 255) / width;
            int g = (y * 255) / height;
            int b = 128;
            COLORREF color = RGB(r, g, b);
            SetPixel(memDC, x, y, color);
        }
    }
    
    //Desenhar borda branca
    HPEN whitePen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
    HPEN oldPen = (HPEN)SelectObject(memDC, whitePen);
    HBRUSH nullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    HBRUSH oldBrush = (HBRUSH)SelectObject(memDC, nullBrush);
    
    Rectangle(memDC, 0, 0, width - 1, height - 1);
    
    SelectObject(memDC, oldPen);
    SelectObject(memDC, oldBrush);
    DeleteObject(whitePen);
    
    //Restaurar e limpar
    SelectObject(memDC, oldBmp);
    DeleteDC(memDC);
    ReleaseDC(nullptr, screenDC);
    
    m_width = width;
    m_height = height;
    
    return true;
}

// Desenha sprite na posição especificada
void Sprite::Draw(HDC hdc, int x, int y) {
    if (!m_bitmap || !hdc) {
        return;
    }
    
    // Criar device context temporário
    HDC tempDC = CreateCompatibleDC(hdc);
    if (!tempDC) {
        return;
    }
    
    // Selecionar bitmap no DC temporário
    HBITMAP oldBmp = (HBITMAP)SelectObject(tempDC, m_bitmap);
    
    // Copiar bitmap para o HDC de destino
    BitBlt(
        hdc,                    // HDC de destino
        x,                      // posição X
        y,                      // posição Y
        m_width,                // largura
        m_height,               // altura
        tempDC,                 // HDC de origem
        0,                      // origem X
        0,                      // origem Y
        SRCCOPY                 // operação de cópia
    );
    
    // Restaurar bitmap anterior e limpar
    SelectObject(tempDC, oldBmp);
    DeleteDC(tempDC);
}