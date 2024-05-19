#version 330 core
in vec2 Texcoord;
out vec4 FragColor;

uniform sampler2D tex;
uniform vec2 screenSize;

void main()
{
    // 获取当前片段的位置
    vec2 uv = Texcoord;

    // 获取屏幕像素位置
    vec2 pixelPos = uv * screenSize;
    
    // 将屏幕像素位置映射到一个固定大小的网格上
    float scale = 10.0; // 控制半色调图案的大小
    vec2 gridPos = floor(pixelPos / scale);

    // 计算网格中心点
    vec2 gridCenter = (gridPos + 0.5) * scale;

    // 获取当前像素距离网格中心的距离
    float dist = length(pixelPos - gridCenter);

    // 从纹理获取颜色
    vec4 color = texture(tex, uv);

    // 计算亮度
    float luminance = 0.299 * color.r + 0.587 * color.g + 0.114 * color.b;

    // 使用亮度值调整点的大小
    float threshold = scale * (1.0 - luminance);

    // 如果距离小于阈值，则绘制黑色点，否则保持原始颜色
    if (dist < threshold)
    {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
    else
    {
        FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
}