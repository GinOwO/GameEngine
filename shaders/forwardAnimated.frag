#version 460 core

in vec2 texCoord0;
in vec3 normal0;
in vec3 worldPos0;

out vec4 finalColor;

struct BaseLight {
	vec3 color;
	float intensity;
};

struct Specular {
	float intensity;
	float exponent;
};

struct DirectionalLight {
	BaseLight base_light;
	vec3 direction;
};

uniform vec3 eyePos;
uniform sampler2D diffuse;

uniform Specular specular;
uniform DirectionalLight directional_light;

vec4 calc_light(BaseLight base_light, vec3 direction, vec3 normal)
{
	float diffuse_factor = dot(normal, -direction);

	vec4 diffuse_color = vec4(0.0);
	vec4 specular_color = vec4(0.0);

	if (diffuse_factor > 0) {
		diffuse_color = vec4(base_light.color, 1.0) *
				base_light.intensity * diffuse_factor;

		vec3 directionToEye = normalize(eyePos - worldPos0);
		vec3 reflectDirection = normalize(reflect(direction, normal));

		float specularFactor = dot(directionToEye, reflectDirection);
		specularFactor = pow(specularFactor, specular.exponent);

		if (specularFactor > 0) {
			specular_color = vec4(base_light.color, 1.0) *
					 specular.intensity * specularFactor;
		}
	}

	return diffuse_color + specular_color;
}

vec4 calc_directional_light(DirectionalLight directional_light, vec3 normal)
{
	return calc_light(directional_light.base_light,
			  -directional_light.direction, normal);
}

void main()
{
	finalColor =
		texture(diffuse, texCoord0.xy) *
		calc_directional_light(directional_light, normalize(normal0));
}
