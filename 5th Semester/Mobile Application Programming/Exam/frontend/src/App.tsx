import {
  IonApp,
  IonRouterOutlet,
  IonSplitPane,
  setupIonicReact,
} from "@ionic/react";
import { IonReactRouter } from "@ionic/react-router";
import { Redirect, Route } from "react-router-dom";
import Menu from "./overlay/menu";
import MockPage from "./core/mock/mockPage";

/* Core CSS required for Ionic components to work properly */
import "@ionic/react/css/core.css";

/* Basic CSS for apps built with Ionic */
import "@ionic/react/css/normalize.css";
import "@ionic/react/css/structure.css";
import "@ionic/react/css/typography.css";

/* Optional CSS utils that can be commented out */
import "@ionic/react/css/padding.css";
import "@ionic/react/css/float-elements.css";
import "@ionic/react/css/text-alignment.css";
import "@ionic/react/css/text-transformation.css";
import "@ionic/react/css/flex-utils.css";
import "@ionic/react/css/display.css";

/* Theme variables */
import "./theme/variables.css";
import ItemsPage from "./items/itemsPage";
import ItemPage from "./items/item/itemPage";
import NewItemPage from "./items/saveItem/newItemPage";
import LoginPage from "./authentication/loginPage";
import PrivateRoute from "./core/privateRoute";

setupIonicReact();

const App: React.FC = () => {
  return (
    <IonApp>
      <IonReactRouter>
        <IonSplitPane contentId="main">
          <Menu />
          <IonRouterOutlet id="main">
            <PrivateRoute path="/" exact>
              <Redirect to="/items" />
            </PrivateRoute>
            <PrivateRoute path="/items" exact>
              <ItemsPage />
            </PrivateRoute>
            <PrivateRoute path="/items/:id" exact>
              <ItemPage />
            </PrivateRoute>
            <PrivateRoute path="/newItem" exact>
              <NewItemPage />
            </PrivateRoute>
            <PrivateRoute path="/folder/:name" exact>
              <MockPage />
            </PrivateRoute>
            <Route path="/login" exact>
              <LoginPage />
            </Route>
          </IonRouterOutlet>
        </IonSplitPane>
      </IonReactRouter>
    </IonApp>
  );
};

export default App;
