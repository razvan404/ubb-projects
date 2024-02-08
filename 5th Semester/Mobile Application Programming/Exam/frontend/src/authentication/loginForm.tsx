import React from "react";
import { Link, useHistory } from "react-router-dom";
import GlobalError from "../core/globalMessage";
import { IonButton, IonInput, IonLabel, IonTitle } from "@ionic/react";
import useAuth from "./useAuth";

import styles from "./styles/loginForm.module.css";
import GlobalLoading from "../core/globalLoading";

const LoginForm = () => {
  const history = useHistory();
  const { currentUser, login, loading, error, setError } = useAuth();
  const [username, setUsername] = React.useState<string>("");

  React.useEffect(() => {
    if (currentUser) {
      history.push("/items");
    }
  }, [currentUser]);

  return (
    <>
      <form
        className={styles.container}
        onSubmit={(ev) => {
          ev.preventDefault();
          login(username);
        }}
      >
        <IonTitle className={styles.title}>Exam PDM</IonTitle>
        <IonInput
          className={styles.input}
          label="Username"
          fill="outline"
          labelPlacement="floating"
          value={username}
          onIonInput={(e) => setUsername(e.detail.value!)}
        />
        <IonButton className={styles.button} type="submit">
          Next!
        </IonButton>
        <IonLabel>Don't have an account yet?</IonLabel>
        <Link to="/login">Just enter your name!</Link>
      </form>
      <GlobalLoading isOpen={loading} />
      <GlobalError message={error} setMessage={setError} />
    </>
  );
};

export default LoginForm;
