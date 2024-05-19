#version 330 core
in vec2 Texcoord;
out vec4 FragColor;

uniform sampler2D tex;
uniform vec2 screenSize;

void main()
{
    // ��ȡ��ǰƬ�ε�λ��
    vec2 uv = Texcoord;

    // ��ȡ��Ļ����λ��
    vec2 pixelPos = uv * screenSize;
    
    // ����Ļ����λ��ӳ�䵽һ���̶���С��������
    float scale = 10.0; // ���ư�ɫ��ͼ���Ĵ�С
    vec2 gridPos = floor(pixelPos / scale);

    // �����������ĵ�
    vec2 gridCenter = (gridPos + 0.5) * scale;

    // ��ȡ��ǰ���ؾ����������ĵľ���
    float dist = length(pixelPos - gridCenter);

    // �������ȡ��ɫ
    vec4 color = texture(tex, uv);

    // ��������
    float luminance = 0.299 * color.r + 0.587 * color.g + 0.114 * color.b;

    // ʹ������ֵ������Ĵ�С
    float threshold = scale * (1.0 - luminance);

    // �������С����ֵ������ƺ�ɫ�㣬���򱣳�ԭʼ��ɫ
    if (dist < threshold)
    {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
    else
    {
        FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
}