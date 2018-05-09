#version 430
#extension GL_ARB_gpu_shader_int64 : require

layout (points) in;
layout (triangle_strip, max_vertices = 24) out;

in vec3 posColor[];
in int vertexID[];
out vec3 geomColor;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform float voxelSize;

struct Light
{
    mat4 lightSpaceMatrix;
    vec3 color;             // all
    int type;               // 0 directional, 1 point light, 2 spot light
    vec3 position;          // spot, point
    float constant;         // spot, point
    vec3 direction;         // dir, spot
    float linear;           // spot, point
    float quadratic;        // spot, point
    float cutOff;           // spot
    float outerCutOff;      // spot
    int64_t shadowMap;      // can be sampler2D or samplerCube
};

layout (std430, binding = LIGHTS_BINDING) readonly buffer LightBuffer
{
    Light lights[];
};

void main() {

    Light currentLight = lights[vertexID[0]];
    if(currentLight.type == 0) // don't render directional lights
    {
        EndPrimitive();
        return;
    }

    vec4 position = gl_in[0].gl_Position;
    geomColor = posColor[0];
    vec4 pos = vec4(1.0f);
    mat4 pvMat = projectionMatrix * viewMatrix;

    vec4[8] offsets = { vec4(-voxelSize, -voxelSize, voxelSize, 0.f),
                        vec4(voxelSize, -voxelSize, voxelSize, 0.f),
                        vec4(-voxelSize, voxelSize, voxelSize, 0.f),
                        vec4(voxelSize, voxelSize, voxelSize, 0.f),
                        vec4(-voxelSize, -voxelSize, -voxelSize, 0.f),
                        vec4(voxelSize, -voxelSize, -voxelSize, 0.f),
                        vec4(-voxelSize, voxelSize, -voxelSize, 0.f),
                        vec4(voxelSize, voxelSize, -voxelSize, 0.f)};

    { // front
        pos = position + offsets[0];    // 1:bottom-left
        gl_Position = pvMat * pos;
        EmitVertex();   

        pos = position + offsets[1];    // 2:bottom-right
        gl_Position = pvMat * pos;
        EmitVertex();

        pos = position + offsets[2];    // 3:top-left
        gl_Position = pvMat * pos;
        EmitVertex();

        pos = position + offsets[3];    // 4:top-right
        gl_Position = pvMat * pos;
        EmitVertex();
    
        EndPrimitive();
    }

    { // back
        pos = position + offsets[5];    // 1:bottom-left
        gl_Position = pvMat * pos;
        EmitVertex();   

        pos = position + offsets[4];    // 2:bottom-right
        gl_Position = pvMat * pos;
        EmitVertex();

        pos = position + offsets[7];    // 3:top-left
        gl_Position = pvMat * pos;
        EmitVertex();

        pos = position + offsets[6];    // 4:top-right
        gl_Position = pvMat * pos;
        EmitVertex();
    
        EndPrimitive();
    }

    { // left
        pos = position + offsets[4];    // 1:bottom-left
        gl_Position = pvMat * pos;
        EmitVertex();   

        pos = position + offsets[0];    // 2:bottom-right
        gl_Position = pvMat * pos;
        EmitVertex();

        pos = position + offsets[6];    // 3:top-left
        gl_Position = pvMat * pos;
        EmitVertex();

        pos = position + offsets[2];    // 4:top-right
        gl_Position = pvMat * pos;
        EmitVertex();
    
        EndPrimitive();
    }

    { // right
        pos = position + offsets[1];    // 1:bottom-left
        gl_Position = pvMat * pos;
        EmitVertex();   

        pos = position + offsets[5];    // 2:bottom-right
        gl_Position = pvMat * pos;
        EmitVertex();

        pos = position + offsets[3];    // 3:top-left
        gl_Position = pvMat * pos;
        EmitVertex();

        pos = position + offsets[7];    // 4:top-right
        gl_Position = pvMat * pos;
        EmitVertex();
    
        EndPrimitive();
    }

    { // top
        pos = position + offsets[2];    // 1:bottom-left
        gl_Position = pvMat * pos;
        EmitVertex();   

        pos = position + offsets[3];    // 2:bottom-right
        gl_Position = pvMat * pos;
        EmitVertex();

        pos = position + offsets[6];    // 3:top-left
        gl_Position = pvMat * pos;
        EmitVertex();

        pos = position + offsets[7];    // 4:top-right
        gl_Position = pvMat * pos;
        EmitVertex();
    
        EndPrimitive();
    }

    { // bottom
        pos = position + offsets[0];    // 1:bottom-left
        gl_Position = pvMat * pos;
        EmitVertex();   

        pos = position + offsets[4];    // 2:bottom-right
        gl_Position = pvMat * pos;
        EmitVertex();

        pos = position + offsets[1];    // 3:top-left
        gl_Position = pvMat * pos;
        EmitVertex();

        pos = position + offsets[5];    // 4:top-right
        gl_Position = pvMat * pos;
        EmitVertex();
    
        EndPrimitive();
    }
}  

