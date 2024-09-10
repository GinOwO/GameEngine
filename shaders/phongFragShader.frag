#version 460 core

const int MAX_POINT_LIGHTS = 4;

in vec2 texCoord0;
in vec3 normal0;
in vec3 worldPos0;

out vec4 finalColor;

struct BaseLight {
	vec3 color;
	float intensity;
};

struct DirectionalLight {
	BaseLight base_light;
	vec3 direction;
};

struct Specular {
	float intensity;
	float exponent;
};

struct Attenuation { // Quadratic formula
	float linear;
	float exponent;
	float constant;
};

struct PointLight {
	BaseLight base_light;
	Attenuation attenuation;
	vec3 position;
};

uniform vec3 base_color;
uniform vec3 ambient_light;
uniform sampler2D sampler;

uniform vec3 eyePos;

uniform DirectionalLight directional_light;
uniform Specular specular;
uniform PointLight point_lights[MAX_POINT_LIGHTS];

vec4 calc_light(BaseLight base_color, vec3 direction, vec3 normal)
{
	float diffuse_factor = dot(normal, -direction);

	vec4 diffuse_color = vec4(0.0);
	vec4 specular_color = vec4(0.0);

	if (diffuse_factor > 0) {
		diffuse_color = vec4(base_color.color, 1.0) *
				base_color.intensity * diffuse_factor;

		vec3 directionToEye = normalize(eyePos - worldPos0);
		vec3 reflectDirection = normalize(reflect(direction, normal));

		float specularFactor = dot(directionToEye, reflectDirection);
		specularFactor = pow(specularFactor, specular.exponent);

		if (specularFactor > 0) {
			specular_color = vec4(base_color.color, 1.0) *
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

vec4 calc_point_light(PointLight point_light, vec3 normal)
{
	vec3 light_direction = worldPos0 - point_light.position;
	float distance_to_point = length(light_direction);
	light_direction = normalize(light_direction);

	vec4 color =
		calc_light(point_light.base_light, light_direction, normal);

	float attenuation =
		0.0000001 + point_light.attenuation.constant +
		(point_light.attenuation.linear * distance_to_point) +
		(point_light.attenuation.exponent * distance_to_point *
		 distance_to_point);

	return color / attenuation;
}

void main()
{
	vec4 total_light = vec4(ambient_light, 1.0);
	vec4 color = vec4(base_color, 1.0);
	vec4 texColor = texture(sampler, texCoord0.xy);

	if (texColor != vec4(0)) {
		color *= texColor;
	}

	vec3 normal = normalize(normal0);

	total_light += calc_directional_light(directional_light, normal);

	for (int i = 0; i < MAX_POINT_LIGHTS; i++) {
		total_light += calc_point_light(point_lights[i], normal);
	}

	finalColor = color * total_light;
}
