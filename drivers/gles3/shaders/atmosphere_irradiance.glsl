[vertex]

layout(location=0) in highp vec4 vertex_attrib;
layout(location=4) in vec2 uv_in;
out vec2 uv_interp;

void main() {
	uv_interp = uv_in;
	gl_Position = vertex_attrib;
}


[fragment]

#define M_PI 3.14159265359
#define FLT_MAX 3.402823466e+38
#define FLT_MIN 1.175494351e-38
#define DBL_MAX 1.7976931348623158e+308
#define DBL_MIN 2.2250738585072014e-308

layout(location=0) out vec4 frag_color;
in vec2 uv_interp;

uniform float atmosphere_outer_radius;
uniform float atmosphere_inner_radius;
uniform vec3 atmosphere_k_ray;
uniform vec3 atmosphere_k_mie;
uniform float atmosphere_k_mie_ex;
uniform float atmosphere_g_mie;
uniform int atmosphere_num_in_scatter;
uniform highp sampler2D atmosphere_lut_ray_mie; //texunit:-6
uniform int atmosphere_irradiance_samples;


// ray intersects sphere
// e = -b +/- sqrt( b^2 - c )
vec2 intersectRaySphere(vec3 ray_origin, vec3 ray_dir, float radius_squared) {
	float b = dot(ray_origin, ray_dir);
	float c = dot(ray_origin, ray_origin) - radius_squared;
	if (c > 0.0 && b > 0.0)	// ray outside of sphere and pointing away
		return vec2(FLT_MAX, -FLT_MAX);
	float d = b * b - c;
	if (d < 0.0)	// ray missing sphere
		return vec2(FLT_MAX, -FLT_MAX);
	d = sqrt( d );
	return vec2(max(0.0,-b-d), -b+d);
}

// Mie
// g : ( -0.75, -0.999 )
//      3 * ( 1 - g^2 )               1 + c^2
// F = ----------------- * -------------------------------
//      8pi * ( 2 + g^2 )     ( 1 + g^2 - 2 * g * c )^(3/2)
float atmospherePhaseMie(float g, float c, float cc) {
	float gg = g * g;
	float a = (1.0 - gg) * (1.0 + cc);
	float b = 1.0 + gg - 2.0 * g * c;
	b *= sqrt(b);
	b *= 2.0 + gg;
	return (3.0 / 8.0 / M_PI) * a / b;
}

// Rayleigh
// g : 0
// F = 3/16PI * ( 1 + c^2 )
float atmospherePhaseRay(float cc) {
	return (3.0 / 16.0 / M_PI) * (1.0 + cc);
}


vec3 atmosphereScatter(in vec3 light_dir, in vec3 ray_pos, in vec3 ray_dir) {
	// "segment" - The ray's line segment that receives scattering from atmosphere.
	// Start with the ray's enter and exit points of the outer atmosphere.
	vec2 segment = intersectRaySphere(ray_pos, ray_dir, atmosphere_outer_radius * atmosphere_outer_radius);
	if( segment.y < 0.0 ) // ray not intersecting atmosphere
		return vec3(0.0);

	vec3 sum_ray = vec3(0.0);
	vec3 sum_mie = vec3(0.0);
	float n_ray0 = 0.0;
	float n_mie0 = 0.0;
	float n_ray1 = 0.0;
	float n_mie1 = 0.0;

	float in_step_len = (segment.y - segment.x) / float(atmosphere_num_in_scatter);
	vec3 in_step = ray_dir * in_step_len;
	vec3 in_pos = ray_pos + ray_dir * segment.x + in_step * 0.5;
	float atmo_thickness = atmosphere_outer_radius-atmosphere_inner_radius;
	for (int i = 0; i < atmosphere_num_in_scatter; i++)
	{
		float in_pos_height = length(in_pos);
		float height_coord = clamp((in_pos_height-atmosphere_inner_radius) / atmo_thickness, 0.0, 1.0);
		float angle_coord = (dot(in_pos/in_pos_height, light_dir) + 1.0) * 0.5;

		vec4 precomputed = texture(atmosphere_lut_ray_mie, vec2(height_coord, angle_coord)).rgba;
		float d_ray = precomputed.r * in_step_len;
		n_ray1 = precomputed.g;
		float d_mie = precomputed.b * in_step_len;
		n_mie1 = precomputed.a;

		n_ray0 += d_ray;
		n_mie0 += d_mie;

		vec3 att = exp(-(n_ray0 + n_ray1) * atmosphere_k_ray -(n_mie0 + n_mie1) * atmosphere_k_mie * atmosphere_k_mie_ex);
		sum_ray += d_ray * att;
		sum_mie += d_mie * att;
		in_pos += in_step;
	}

	float c  = dot( ray_dir, -light_dir );
	float cc = c * c;
	vec3 scatter = sum_ray * atmosphere_k_ray * atmospherePhaseRay(cc)
	             + sum_mie * atmosphere_k_mie * atmospherePhaseMie(atmosphere_g_mie, c, cc);

	return scatter;
}



void main() {
	// distance from atmosphere center
	float dist = atmosphere_inner_radius + uv_interp.x * (atmosphere_outer_radius - atmosphere_inner_radius);
	// angle from vertical to light direction (1.0 straight up, 0.0 horizontal, -1.0 straight down
	float angle = uv_interp.y * 2.0 - 1.0;

	vec3 ray_ori = vec3(0.0, dist, 0.0);
	vec3 light_dir = vec3(1.0-abs(angle), angle, 0.0);

	float phi_step = M_PI / atmosphere_irradiance_samples;
	float theta_step = M_PI / atmosphere_irradiance_samples;

	vec3 sum = vec3(0.0);
	for (int j = 0; j < atmosphere_irradiance_samples / 2; ++j) {
		float theta = (j + 0.5) * theta_step;
		float weight = theta_step * phi_step * sin(theta);
		for (int i = 0; i < 2 * atmosphere_irradiance_samples; ++i) {
			float phi = (i + 0.5) * phi_step;
			vec3 ray_dir = vec3(cos(phi) * sin(theta), cos(theta), sin(phi) * sin(theta));
			sum += atmosphereScatter(light_dir, ray_ori, ray_dir) * weight;
		}
	}

	frag_color = vec4(sum,0.0);
}
