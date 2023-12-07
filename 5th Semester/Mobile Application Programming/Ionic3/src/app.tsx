import { IonApp, IonRouterOutlet, setupIonicReact } from "@ionic/react";
import { IonReactRouter } from "@ionic/react-router";
import { Route } from "react-router-dom";
import { RecoilRoot } from "recoil";
import { DefaultRoute, PrivateRoute, routes } from "./routing";

import "@ionic/react/css/core.css";

import "@ionic/react/css/normalize.css";
import "@ionic/react/css/structure.css";
import "@ionic/react/css/typography.css";

import "@ionic/react/css/padding.css";
import "@ionic/react/css/float-elements.css";
import "@ionic/react/css/text-alignment.css";
import "@ionic/react/css/text-transformation.css";
import "@ionic/react/css/flex-utils.css";
import "@ionic/react/css/display.css";

import "./theme/variables.css";

setupIonicReact();

const App = () => (
  <RecoilRoot>
    <IonApp>
      <IonReactRouter>
        <IonRouterOutlet>
          <DefaultRoute />
          {routes.map((route, index) =>
            route.isPrivate ? (
              <PrivateRoute key={index} {...route} />
            ) : (
              <Route key={index} {...route} />
            )
          )}
        </IonRouterOutlet>
      </IonReactRouter>
    </IonApp>
  </RecoilRoot>
);

export default App;
