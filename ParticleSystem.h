#include <SFML/Graphics.hpp>
#include <math.h>

using namespace sf;
using namespace std;

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
    float size;
    int type; //0: spread out, 1: cone, 2: burst, 3: cone burst
    bool dontRespawn = false;
    int timeAlive = 0;
    float baseSpeed = 50.f;
    Color color;
    ParticleSystem(unsigned int count, float Lifetime, float Size, float Speed, int Type, Color COLOR) :
    m_particles(count),
    m_vertices(sf::Quads, count),
    m_lifetime(sf::seconds(3.f)),
    m_emitter(0.f, 0.f)
    {
        size = Size;
        type = Type;
        color = COLOR;
        timeAlive = Lifetime;
        baseSpeed = Speed;
    }

    void setEmitter(sf::Vector2f position)
    {
        m_emitter = position;
        if (type == 2 or type == 3)
            dontRespawn = false;
    }

    void update(sf::Time elapsed)
    {
        for (std::size_t i = 0; i < m_particles.size()/4; ++i)
        {
            // update the particle lifetime
            Particle& p = m_particles[i * 4];
            p.lifetime -= elapsed;

            // if the particle is dead, respawn it
            if (p.lifetime <= sf::Time::Zero)
            {
                resetParticle(i * 4);
                resetParticle(i * 4 + 1);
                resetParticle(i * 4 + 2);
                resetParticle(i * 4 + 3);
            }
            

            // update the position of the corresponding vertex
             //m_vertices[i].position += p.velocity * elapsed.asSeconds();
             m_vertices[i * 4].position += p.velocity * elapsed.asSeconds();
             m_vertices[i * 4 + 1].position = m_vertices[i * 4].position + sf::Vector2f(size, 0);
             m_vertices[i * 4 + 2].position = m_vertices[i * 4].position + sf::Vector2f(size, size);
             m_vertices[i * 4 + 3].position = m_vertices[i * 4].position + sf::Vector2f(0, size);

            // update the alpha (transparency) of the particle according to its lifetime
            float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
            for (int j = i * 4; j < i * 4 + 4; j++)
            { 
                m_vertices[j].color.a = static_cast<sf::Uint8>(255);
                m_vertices[j].color.r = static_cast<sf::Uint8>(color.r);
                m_vertices[j].color.g = static_cast<sf::Uint8>(color.g);
                m_vertices[j].color.b = static_cast<sf::Uint8>(color.b);
            }
        }
        
        if (type == 2 or type == 3)
            dontRespawn = true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        //states.transform *= getTransform();

        // our particles don't use a texture
        //states.texture = NULL;

        // draw the vertex array
        //target.draw(m_vertices, states);
        target.draw(m_vertices);
    }

private:

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    void resetParticle(std::size_t index)
    {
        // give a random velocity and lifetime to the particle
        float angle;
        if (type == 0 or type == 2)
            angle = (std::rand() % 360) * 3.14f / 180.f;
        if (type == 1 or type == 3)
            angle = (std::rand() % 90) * 3.14f / 180.f - 180;
        float speed = (std::rand() % 50) + baseSpeed;
        m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        m_particles[index].lifetime = sf::milliseconds((std::rand() % 1000) + timeAlive);

        // reset the position of the corresponding vertex
        if (dontRespawn == false)
        {
            m_vertices[index].position = m_emitter;
        }
        else
            m_vertices[index].position = sf::Vector2f(-10000, -10000);
    }

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
};
