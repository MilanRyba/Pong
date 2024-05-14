#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include "Walnut/Input/Input.h"
#include "Pong.h"

class PongLayer : public Walnut::Layer
{
public:
	PongLayer() {}

	virtual void OnUpdate(float ts) override
	{
		// if (Walnut::Input::IsKeyDown(Walnut::KeyCode::Space))
		// 	mPong.StartGame(Pong::Modifier::AdditivePointSystem);

		mPong.OnUpdate(ts);
		mPong.OnRender();
	}

	// Takes the final image and renders it to the window
	virtual void OnUIRender() override
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Viewport");

		std::shared_ptr<Walnut::Image> image = mPong.GetImage();
		if (image)
			ImGui::Image(image->GetDescriptorSet(), ImVec2((float)image->GetWidth(), (float)image->GetHeight()));

		ImGui::End();

		uint32_t left_score = mPong.GetLeftScore();
		uint32_t right_score = mPong.GetRightScore();

		ImGui::Begin("Led Line");

		Pong::Modifier mod = mPong.GetModifier();
		if (EnumHasAnyFlags(mod, Pong::Modifier::AdditivePointSystem))
		{
			auto* draw_list = ImGui::GetWindowDrawList();
			ImVec2 window_pos = ImGui::GetWindowPos();
			uint32_t points = mPong.GetBounces();

			ImVec2 min(window_pos.x + 10, window_pos.y + 40);
			ImVec2 max(window_pos.x + 20, window_pos.y + 50);
			for (int i = 31; i >= 0; i--)
			{
				if (i < points)
					draw_list->AddRectFilled(min, max, 0xffffffff);
				else
					draw_list->AddRectFilled(min, max, 0xff000000);

				min.x += 20;
				max.x += 20;
			}
		}
		else
		{
			auto* draw_list = ImGui::GetWindowDrawList();
			ImVec2 window_pos = ImGui::GetWindowPos();

			ImVec2 min(window_pos.x + 10, window_pos.y + 40);
			ImVec2 max(window_pos.x + 20, window_pos.y + 50);

			for (int i = 0; i < 16; i++)
			{
				if (i < left_score)
					draw_list->AddRectFilled(min, max, 0xffffffff);
				else
					draw_list->AddRectFilled(min, max, 0xff000000);

				min.x += 20;
				max.x += 20;
			}

			for (int i = 15; i >= 0; i--)
			{
				if (i < right_score)
					draw_list->AddRectFilled(min, max, 0xffffffff);
				else
					draw_list->AddRectFilled(min, max, 0xff000000);

				min.x += 20;
				max.x += 20;
			}
		}

		ImGui::End();

		uint32_t led_color = 0xff000000;
		if (EnumHasAnyFlags(mod, Pong::Modifier::AdditivePointSystem))
		{
			led_color += 0xff8b3d48;
		}

		if (EnumHasAnyFlags(mod, Pong::Modifier::AcceleratingBall))
		{
			led_color += 0xff00a5ff;
		}

		ImGui::Begin("RGB Led Diodes");
		{
			auto* draw_list = ImGui::GetWindowDrawList();
			ImVec2 window_pos = ImGui::GetWindowPos();

			ImVec2 min(window_pos.x + 10, window_pos.y + 40);
			ImVec2 max(window_pos.x + 40, window_pos.y + 70);
			draw_list->AddRectFilled(min, max, led_color);

			min.x += 50;
			max.x += 50;
			draw_list->AddRectFilled(min, max, led_color);
		}
		ImGui::End();

		ImGui::PopStyleVar();

		mPong.GetMenu()->OnRender();
	}

private:
	Pong::Pong mPong;
};

/*
* Vytváøím tady okno o velikosti toho lcd displaye (nelze resiznout) a v nìm se samoøejmì renderurje naše hra. 
* Okolo ti taky vyskoèila další okna. To je gui knihovna ImGui. 'Pokusil' jsem se tím emulovat UI v naší høe, 
* jelikož renderovat text jako takový tu nejde.
* 
* Jedno je Main Menu a mùžeš pomocí Enter zvolit jestli chceš hrát nebo si vybrat modifikátory.
* ! Modifikátory vybereš pomocí Enter, ale tak jak to funguje, tak ta aplikace se jen kouká jestli je Enter zmáèklej, takže 
* se ten mod mùže zapnout, vypnout... !
* Escape aby ses vrátil do hlavního menu
* 
* Play zaène novou hru. Spacebar pro vypuštìní míèe. W, S - pohyb èerveného hráèe, Up, Down - pohyb modrého hráèe.
* 
* 'Emuloval' jsem i ty periferije. RGB led mìní barvu podle modifikátorù
*/

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Pong - Graphics";
	spec.Width = 480;
	spec.Height = 320;
	spec.WindowResizeable = false;

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<PongLayer>();
	return app;
}
