#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "Core/Factory.h"
#include "Components/ColliderComponent.h"


namespace nu {
	void Scene::AddActor(unique_ptr<Actor> actor) {
		actor->m_scene = this;
		m_pendingActors.push_back(move(actor)); 
	}
	void Scene::RemoveAllActors(){m_actors.clear();}

	bool Scene::Load(const string& sceneName){
		nu::json::document_t document;
		if (nu::json::Load("Data/scene.json", document)) {
			if (JSON_HAS_NAME(document, "actors")) {
				for (auto& actorValue : JSON_GET_NAME(document, "actors").GetArray()) {

					string typeName;
					JSON_READ_NAME(actorValue, "type", typeName);

					auto actor = Factory::Instance().Create<Actor>(typeName);
					actor->Read(actorValue);

					bool prototype = false;
					JSON_READ(actorValue, prototype);

					if (prototype) { 
						string name;
						JSON_READ(actorValue, name);
						Factory::Instance().RegisterProtoype<Actor>(name, move(actor)); 
					}
					else {
						AddActor(move(actor));
					}
				}
			}
		}
		else { return false; }

		//	string type;
		//	JSON_READ(document, type);
//
		//	auto actor = Factory::Instance().Create<Actor>(type);
		//	actor->Read(document);
		//	cout << actor->GetName() << endl;
		//	cout << actor->GetTag() << endl;
		//	cout << actor->GetTransform().rotation << endl;
//
		//	Factory::Instance().RegisterProtoype<Actor>("PlayerPrototype", move(actor));
		//}

		return true;
	}

	void Scene::Update(float dt) {
		//Update Actors
		for (auto& actor : m_actors) {
			actor->Update(dt);
		}

		//Updtae Collisions
		UpdateCollisions();

		//Remove Destroyed Actors
		std::erase_if(m_actors, [](auto& actor) {return actor->m_destroyed; });

		//Add Pending Actors
		for (auto& actor : m_pendingActors) { m_actors.push_back(move(actor));}
		m_pendingActors.clear();
	};

	void Scene::Draw(const class Renderer& renderer){
		for (const auto& actor : m_actors) {
			if (actor) {
				actor->Draw(renderer);
			}
		}
	}
	void Scene::UpdateCollisions()
	{
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				if (actorA == actorB || actorA-> m_destroyed || actorB->m_destroyed) continue;

				auto colliderA = actorA->GetComponent<ColliderComponent>();
				auto colliderB = actorB->GetComponent<ColliderComponent>();

				if (!colliderA || !colliderB) continue;

				//Check Collision
				if (colliderA->CheckCollision(*colliderB)) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	};
}