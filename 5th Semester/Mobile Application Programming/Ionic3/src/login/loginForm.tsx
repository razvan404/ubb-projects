import * as React from "react";
import { IonButton, IonInput, IonItem, IonLabel, IonTitle } from "@ionic/react";

import styles from "./styles/loginForm.module.css";
import { Link } from "react-router-dom";
import { useAuth } from "../auth";
import { GlobalError } from "../extra/globalMessage";

const LoginForm = () => {
  const { currentUser, login, loading, error, setError } = useAuth();
  const [usernameOrEmail, setUsernameOrEmail] = React.useState<string>("");
  const [password, setPassword] = React.useState<string>("");

  React.useEffect(() => {
    if (currentUser) {
      location.href = "/gallery";
    }
  }, [currentUser]);

  return (
    <>
      <form
        className={styles.container}
        onSubmit={(ev) => {
          ev.preventDefault();
          console.log(usernameOrEmail, password);
          login(usernameOrEmail, password);
        }}
      >
        <IonTitle className={styles.title}>Art Gallery</IonTitle>
        <IonInput
          className={styles.input}
          label="Username or Email"
          fill="outline"
          labelPlacement="floating"
          value={usernameOrEmail}
          onIonInput={(e) => setUsernameOrEmail(e.detail.value!)}
        />
        <IonInput
          className={styles.input}
          type="password"
          label="Password"
          fill="outline"
          labelPlacement="floating"
          value={password}
          onIonInput={(e) => setPassword(e.detail.value!)}
        />
        <IonButton className={styles.button} type="submit">
          Login
        </IonButton>
        <IonLabel>Don't have an account yet?</IonLabel>
        <Link to="/register">Register now!</Link>
      </form>
      <GlobalError message={error} setMessage={setError} />
    </>
  );
};

export default LoginForm;
