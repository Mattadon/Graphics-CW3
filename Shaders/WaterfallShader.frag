#version 400 core
struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct PointLight
{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};

struct DirLight
{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	float cutoff;
	float outerCutoff;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 texCoordFrag;
in vec3 fragPos;
in vec3 normalVec;
in vec4 lightSpaceFrag;

out vec4 colour;

uniform vec3 viewPos;
uniform Material material;
uniform float timeOffset;

uniform DirLight sunLight;
#define NR_POINT_LIGHTS 2 
uniform PointLight pointLights[NR_POINT_LIGHTS];
//uniform SpotLight spotLight;
uniform sampler2D shadowMap;

vec3 celAmbient(vec3 ambientInput)
{
	return (vec3(texture2D(material.diffuse, vec2(texCoordFrag.x, texCoordFrag.y + timeOffset))) * ambientInput);
}

vec3 celDiffuse(vec3 normals, vec3 lightDirection, vec3 diffuseInput)
{
	const float stepA = 0.1;
	const float stepB = 0.3;
	const float stepC = 0.5;
	const float stepD = 1.0;
	
    float diffFactor = max(dot(normals, lightDirection), 0.0);
	if(diffFactor < 0.3)
		diffFactor = 0.0;
	else
		diffFactor = stepD;
    return (diffFactor * vec3(texture2D(material.diffuse, vec2(texCoordFrag.x, texCoordFrag.y + timeOffset))) * diffuseInput);
}

vec3 celSpecular(vec3 normals, vec3 lightDirection, vec3 specularInput)
{
	vec3 viewDirection = normalize(viewPos - fragPos);
    vec3 reflectDirection = reflect(-lightDirection, normals);
    float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
	if(specularFactor < 0.5)
		specularFactor = 0.0;
	else specularFactor = 1.0;
    return (specularFactor * vec3(texture2D(material.specular, vec2(texCoordFrag.x, texCoordFrag.y + timeOffset))) * specularInput);
}

vec3 calculateDirLight(DirLight light, vec3 normals, float shadows, vec3 lightDirection)
{
	//vec3 lightDirection = normalize(-light.direction);
	
	vec3 ambientLight = celAmbient(light.ambient);
	vec3 diffuseLight = celDiffuse(normals, lightDirection, light.diffuse);
	vec3 specularLight = celSpecular(normals, lightDirection, light.specular);
	
	return (ambientLight + shadows * (diffuseLight + specularLight));
}

vec3 calculatePointLight(PointLight light, vec3 normals, float shadows)
{
	float distance    = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	vec3 lightDirection = normalize(light.position - fragPos);
	
	vec3 ambientLight = celAmbient(light.ambient) * attenuation;
	vec3 diffuseLight = celDiffuse(normals, lightDirection, light.diffuse) * attenuation;
	vec3 specularLight = celSpecular(normals, lightDirection, light.specular) * attenuation;
	
	return (ambientLight + shadows* (diffuseLight + specularLight));
}

vec3 calculateSpotLight(SpotLight light, vec3 normals, float shadows)
{
	vec3 lightDirection = normalize(light.position - fragPos);
	float theta = dot(lightDirection, normalize(-light.direction));
	   
	float intensity = 0.0;
	if(theta > light.outerCutoff && theta <= light.cutoff)
	{
		intensity = 0.5f;
	}
	if(theta > light.cutoff) 
	{       
		intensity = 1.0f;
	}
  
	vec3 ambientLight = celAmbient(light.ambient);
	vec3 diffuseLight = celDiffuse(normals, lightDirection, light.diffuse) * intensity;
	vec3 specularLight = celSpecular(normals, lightDirection, light.specular) * intensity;
		
	return (ambientLight + shadows * (diffuseLight + specularLight));
}

float calculateShadows(vec3 lightDir, vec3 normals, vec4 lightSpaceFrag)
{
    vec3 projCoords = lightSpaceFrag.xyz / lightSpaceFrag.w;
	projCoords = projCoords * 0.5 + 0.5; 
	
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z; 
	
	float bias = max(0.05 * (1.0 - dot(normals, lightDir)), 0.005); 
	//float bias = 0.005;
	if(currentDepth > 1.0 || currentDepth - bias > closestDepth)
	{
		return 0.0;
	}
	else
	{
		return 1.0;
	}
}

void main()
{
	vec3 normals = normalize(normalVec);

	vec3 lightDirection = normalize(-sunLight.direction);
	float shadow = calculateShadows(lightDirection, normals, lightSpaceFrag);
	
	vec3 result;
	result += calculateDirLight(sunLight, normals, shadow, lightDirection);

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += calculatePointLight(pointLights[i], normals, shadow);

    //result += calculateSpotLight(spotLight, normals, shadow);    
    
    colour = vec4(result, 1.0);
}
