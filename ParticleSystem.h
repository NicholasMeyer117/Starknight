#include <SFML/Graphics.hpp>
#include <math.h>

using namespace sf;
using namespace std;

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
    float size;
    int type; //0: spread out, 1: cone, 2: burst, 3: cone burst, 4: Background
    bool dontRespawn = false;
    int timeAlive = 0;
    float baseSpeed = 50.f;
    float baseAngle;
    float spawnSpeed;
    int maxH, minH, maxW, minW;
    int firsts;
    int opacity;
    Color color;
    ParticleSystem(unsigned int count, float Lifetime, float Size, float Speed, int Type, Color COLOR, float Angle = 90.f, 
    int MaxH = 0, int MinH = 0, int MaxW = 0, int MinW = 0, int Opacity = 255) :
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
        baseAngle = Angle;
        maxW = MaxW;
        minW = MinW;
        maxH = MaxH;
        minH = MinH;
        firsts = count;
        opacity = Opacity;
        
    }

    void setEmitter(sf::Vector2f position)
    {
        if (type == 2 or type == 3)
            dontRespawn = false;
        m_emitter = position;
    }

    void update(sf::Time elapsed)
    {
        for (std::size_t i = 0; i < m_particles.size()/4; ++i)
        {
            // update the particle lifetime
            Particle& p = m_particles[i * 4];
            p.lifetime -= elapsed;

            // if the particle is dead, respawn it
            if (p.lifetime <= sf::Time::Zero or (type == 4 and m_vertices[i * 4].position.x <= 0))
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
                m_vertices[j].color.a = static_cast<sf::Uint8>(opacity);
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
        else if (type == 1 or type == 3)
            angle = (std::rand() % 90) * 3.14f / 180.f - baseAngle;
        float speed = (std::rand() % 50) + baseSpeed;
        if (type!=4)
            m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        else 
        {
            speed = baseSpeed;
            m_particles[index].velocity = sf::Vector2f(-1 * speed, 0 * speed);
        }
        m_particles[index].lifetime = sf::milliseconds((std::rand() % 1000) + timeAlive);

        // reset the position of the corresponding vertex
        if (dontRespawn == false)
        {
            m_vertices[index].position = m_emitter;
            
            if (type == 4)
            {
                m_emitter.y = (std::rand() % (maxH-minH));// + minH;
                if (firsts > 0)
                {
                    firsts--;
                    m_emitter.x = (std::rand() % (maxW-minW));
                }
                else
                {
                    m_emitter.x = maxW;
                }
                m_vertices[index].position = m_emitter;
            }
        }
        else
        {
            m_vertices[index].position = sf::Vector2f(-10000, -10000);
            
        }
    }

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
};
