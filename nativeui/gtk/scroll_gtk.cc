// Copyright 2016 Cheng Zhao. All rights reserved.
// Use of this source code is governed by the license that can be found in the
// LICENSE file.

#include "nativeui/scroll.h"

namespace nu {

void Scroll::PlatformInit(const Size& size) {
  SetPreferredSize(size);
  TakeOverView(gtk_scrolled_window_new(nullptr, nullptr));
  gtk_container_add(GTK_CONTAINER(view()), gtk_viewport_new(nullptr, nullptr));
  SetBounds(Rect(size));
}

void Scroll::PlatformSetContentView(Container* container) {
  GtkWidget* viewport = gtk_bin_get_child(GTK_BIN(view()));
  GtkWidget* child = gtk_bin_get_child(GTK_BIN(viewport));
  if (child)
    gtk_container_remove(GTK_CONTAINER(viewport), child);
  gtk_container_add(GTK_CONTAINER(viewport), container->view());

  container->Layout();
}

void Scroll::SetVerticalScrollBar(bool has) {
  GtkPolicyType hp;
  gtk_scrolled_window_get_policy(GTK_SCROLLED_WINDOW(view()), &hp, nullptr);
  GtkPolicyType vp = has ? GTK_POLICY_ALWAYS : GTK_POLICY_NEVER;
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(view()), hp, vp);
}

bool Scroll::HasVerticalScrollBar() const {
  GtkPolicyType vp;
  gtk_scrolled_window_get_policy(GTK_SCROLLED_WINDOW(view()), nullptr, &vp);
  return vp == GTK_POLICY_ALWAYS;
}

void Scroll::SetHorizontalScrollBar(bool has) {
  GtkPolicyType vp;
  gtk_scrolled_window_get_policy(GTK_SCROLLED_WINDOW(view()), nullptr, &vp);
  GtkPolicyType hp = has ? GTK_POLICY_ALWAYS : GTK_POLICY_NEVER;
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(view()), hp, vp);
}

bool Scroll::HasHorizontalScrollBar() const {
  GtkPolicyType hp;
  gtk_scrolled_window_get_policy(GTK_SCROLLED_WINDOW(view()), &hp, nullptr);
  return hp == GTK_POLICY_ALWAYS;
}

void Scroll::SetAutoHideScrollBar(bool is) {
  GtkPolicyType p = is ? GTK_POLICY_AUTOMATIC : GTK_POLICY_NEVER;
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(view()), p, p);
}

bool Scroll::IsScrollBarAutoHide() const {
  GtkPolicyType hp, vp;
  gtk_scrolled_window_get_policy(GTK_SCROLLED_WINDOW(view()), &hp, &vp);
  return hp == GTK_POLICY_AUTOMATIC && vp == GTK_POLICY_AUTOMATIC;
}

}  // namespace nu
