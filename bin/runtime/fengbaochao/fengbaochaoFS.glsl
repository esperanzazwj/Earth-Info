in vec4 _col;
uniform vec4 func;//����ר�õģ���������У�ֱ��ǰ����Ϊ0��ok
out vec4 fragmentColor;
in vec3 worldPosition;
void main()
{
    if(abs(func.x + func.y + func.z) >0.01)
    {
	if(worldPosition.x * func.x + worldPosition.y* func.y + worldPosition.z* func.z + func.w < 0)
	discard;
    }
    fragmentColor = _col;
}